const VirtualMachine = require('../../nitrobolt/scratch-vm/src/virtual-machine');
const log = require('../../nitrobolt/scratch-vm/src/util/log');
const fs = require('fs');
const { resolve } = require('path');

const vm = new VirtualMachine();
let frameRendered = false;

// Don't care about missing storage
const warn = log.warn;
log.warn = (...args) => {
  if (!String(args[0]).startsWith('No storage module present;')) {
    warn(...args);
  }
};

const fail = msg => {
  vm.quit();
  console.error('Smoke failed: ' + String(msg));
  process.exit(1);
};

vm.loadProject(fs.readFileSync(resolve('./doom.sb3'))).then(() => {
  // Disable compiler so we can override block functions
  vm.setCompilerOptions({enabled: false, warpTimer: false});

  vm.runtime._primitives.sensing_askandwait = args => fail(args.QUESTION);
  const changeX = vm.runtime._primitives.motion_changexby;
  vm.runtime._primitives.motion_changexby = (...args) => {
    frameRendered = true;
    return changeX(...args);
  };

  vm.start();
  vm.greenFlag();

  setTimeout(() => {
    if (!frameRendered) {
      fail('renderer did not draw a frame');
    }
    vm.quit();
    console.log('Smoke passed');
    process.exit(0);
  }, 1000 * 15);
}).catch(fail);
