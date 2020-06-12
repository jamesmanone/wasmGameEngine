"use strict";
(function() {

  const c = document.createElement('canvas');
  const ctx = c.getContext("2d");
  c.height = 720;
  c.width = 1280;

  document.getElementsByTagName('body')[0].appendChild(c);

  function draw(data) {
    ctx.putImageData(new ImageData(data, c.width), 0, 0);
  }

  function messageHandle({data}) {
    if(data.type = 'frame') draw(data.data);
  }

  const thread = new Worker("/worker.js");
  thread.onmessage = messageHandle;
  thread.postMessage({w: c.width, h: c.height});

}).bind({})();