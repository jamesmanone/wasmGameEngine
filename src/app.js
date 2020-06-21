"use strict";

class Handler {
  constructor(w, h, ctx) {
    this.fetching = false;
    this.ctx = ctx;
    this.width = w;
    this.height = h;
    this.getWasm.call(this);
    this.step = this.step.bind(this);
  }

  drawScreen(pointer, w) {

    let fb = new Uint8ClampedArray(this.instance.exports.memory.buffer, pointer, this.width*this.height*4);

    // let buff = new ArrayBuffer(this.width * this.height * 4)
    // let fb2 = new Uint8ClampedArray(buff);
  
    // fb.forEach((v, i) => fb2[i] = v);

    // self.postMessage({type: "frame", data: fb2}, [buff]);
    this.ctx.putImageData(new ImageData(fb, this.width), 0, 0);
  }

  println(pointer) {
    const line = [];
    const buffer = new Uint8Array(this.instance.exports.memory.buffer, pointer);
    let i = 0;
    while(buffer[i] != 0) line.push(buffer[i++])
    this.instance.exports.free(pointer);
  
    console.log(String.fromCharCode(...line));
  }

  loop() {
    this.instance.exports.step();
  }

  now() {
    return performance.now();
  }

  step() {
    if(!(this.instance && this.instance.exports)) this.getWasm.call(this);
    else {
      this.instance.exports.step();
      requestAnimationFrame(this.step);
    }
  }

  getWasm() {
    if(this.fetching) return;
    this.fetching = true;
    fetch("/singlethread.wasm")
      .then(r => r.arrayBuffer())
      .then(bytes => WebAssembly.instantiate(bytes, {
        env: {
          memory: new WebAssembly.Memory({initial: 256, maximum: 32768}),
          drawScreen: this.drawScreen.bind(this),
          println: this.println.bind(this),
          now: this.now,
          _ZN3v2dIiED1Ev: n => n,
          emscripten_notify_memory_growth: () => {}
        },
        wasi_snapshot_preview1: {
          proc_exit: n=>{}
        }
      }))
      .then(({instance}) => {
        this.instance = instance;
        this.memory = new Uint8Array(instance.exports.memory.buffer);
      })
      // .then(() => setInterval(this.instance.exports.step, 20))
      .then(() => {
        this.instance.exports.setWH(this.width, this.height);
        requestAnimationFrame(this.step);
      });
  }
}


(function() {

  const c = document.createElement('canvas');
  const ctx = c.getContext("2d");
  c.height = window.innerHeight >= 720 ? 720 : window.innerHeight;
  if(window.innerWidth >= (c.height/9)*16) c.width = (c.height/9)*16;
  else {
    c.width = window.innerWidth;
    c.height = (c.width/16)*9;
  }

  document.getElementsByTagName('body')[0].appendChild(c);
  if(!!window.SharedArrayBuffer) {
    console.log("Using worker thread");

    function draw(pointer) {
      const fb = new Uint8ClampedArray(this.memory.buffer, pointer, c.height*c.width*4);
      ctx.putImageData(new ImageData(fb.slice(), c.width), 0, 0);
    }

    function setBuffer(memory) {
      this.memory = memory;
    }

    function messageHandle({data}) {
      if(data&&data.pointer) draw.call(this, data.pointer);
      else setBuffer.call(this, data);
    }

    this.thread = new Worker("/worker.js");
    this.thread.onmessage = messageHandle.bind(this);
    this.thread.postMessage({w: c.width, h: c.height});

  } else {
    console.log("Fallback to single thread");
    const handler = new Handler(c.width, c.height, ctx);
    // requestAnimationFrame(handler.step);
  }
  

}).bind({})();