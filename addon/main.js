var addon = require("bindings")("my_cpp_addon");

addon.myPrint();

console.log(addon.addThree(5));
console.log(addon.addThree(10.2));

console.log(addon.addInts(2, 3));
console.log(addon.addInts(1.2, 4));

console.log(`True is the new ${addon.flipBool(true)}`);

const Colors = {
    Red: 0,
    Green: 1,
    Blue: 2,
};

console.log(`Green has a value of ${addon.enumValue(Colors.Green)}`);
const myColor = addon.currentColor();
console.log(
    `Current color: ${Object.keys(Colors).find((key) => Colors[key] === 2)}`
);
