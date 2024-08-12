let Buf = null;
let compile = () => {
  console.log("\033c");
  console.log('--file changed');
  const ls = require('child_process').spawn('clang-18', '-std=c++23 -O3 --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -Wno-unused-command-line-argument -Wno-string-compare -g3 -gdwarf-5 -o - xindex.cpp'.split(' '));
  let buf = Buffer.alloc(0);
  ls.stdout.on('data', (chunk) => buf = Buffer.concat([buf, chunk]));
  ls.stderr.on('data', (data) => console.error(data.toString()));
  ls.on('close', (code) => {
    console.log('child process exited with code:' + code);
    Buf = buf;
  });
}
compile();

require('http').createServer((req, res) => {
  if (req.url == '/') return res.end(require('fs').readFileSync('./xindex.html'));
  if (req.url == '/xbundle.wasm') { res.setHeader('content-type', 'application/wasm'); return res.end(Buf); }
  if (req.url == '/xbundle.wasm.dwp') { res.setHeader('content-type', 'application/wasm'); return res.end(Buf); }
  if (req.url == '/font') { return res.end(require("fs").readFileSync("./xmenlo.ttf")); }
  console.log(req.url);
}).listen(3000);

console.log('listen');

let Flag = false;
require('fs').watch('./xindex.cpp', () => {
  if (Flag) return;
  Flag = true;
  setTimeout(() => { Flag = false; }, 100);
  compile();
});