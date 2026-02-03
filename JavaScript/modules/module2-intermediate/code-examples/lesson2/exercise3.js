// Exercise 3: Spread and Rest
function combineArrays(...arrays) {
    return arrays.flat();
}

let arr1 = [1, 2];
let arr2 = [3, 4];
let arr3 = [5, 6];

let result = combineArrays(arr1, arr2, arr3);
console.log(result); // [1, 2, 3, 4, 5, 6]
