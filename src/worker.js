class Handler {
  constructor(w, h) {
    this.width = w;
    this.height = h;
    this.getWasm.bind(this)()
  }

  drawScreen(pointer, w) {

    let fb = new Uint8ClampedArray(this.instance.exports.memory.buffer, pointer, this.width*this.height*4);

    let buff = new ArrayBuffer(this.width * this.height * 4)
    let fb2 = new Uint8ClampedArray(buff);
  
    fb.forEach((v, i) => fb2[i] = v);

    self.postMessage({type: "frame", data: fb2}, [buff]);
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

  getWasm() {
    fetch("/tst.wasm")
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
        while(1) this.instance.exports.step();
      });
  }

  
}

self.onmessage = ({data}) => {
  if(data.h && data.w) self.handler = new Handler(data.w, data.h);
  else debugger;
}