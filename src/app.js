"use strict";
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