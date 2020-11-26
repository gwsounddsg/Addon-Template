var addon = require("bindings")("my_cpp_addon");

addon.myPrint();

console.log(addon.addThree(5));
console.log(addon.addThree(10.2));
