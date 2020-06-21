class Handler {
  constructor(w, h) {
    this.width = w;
    this.height = h;
    // this.memory = new WebAssembly.Memory({initial: 256, maximum: 32768, shared: true});
    // self.postMessage(this.memory);
    this.getWasm.bind(this)();
  }

  drawScreen(pointer, w) {
    self.postMessage({pointer: pointer, w: w});
  }

  println(pointer) {
    const line = [];
    const buffer = new Uint8Array(this.memory.buffer, pointer);
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

  onGrowMemory() {
    self.postMessage(this.memory);
  }

  getWasm() {
    fetch("/multithreaded.wasm")
      .then(r => r.arrayBuffer())
      .then(bytes => WebAssembly.instantiate(bytes, {
        env: {
          // memory: this.memory,
          drawScreen: this.drawScreen.bind(this),
          println: this.println.bind(this),
          now: this.now,
          _ZN3v2dIiED1Ev: n => n,
          emscripten_notify_memory_growth: this.onGrowMemory.bind(this)
        },
        wasi_snapshot_preview1: {
          proc_exit: n=>{}
        }
      }))
      .then(({instance}) => {
        this.instance = instance;
        this.memory = this.instance.exports.memory;
        self.postMessage(this.memory);
      })
      .then(() => {
        this.instance.exports.setWH(this.width, this.height);
        this.instance.exports.go();
      });
  }

  
}

self.onmessage = ({data}) => {
  if(data.h && data.w) self.handler = new Handler(data.w, data.h);
  else debugger;
}