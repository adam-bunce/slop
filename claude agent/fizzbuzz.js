/**
 * FizzBuzz implementation
 * Prints numbers from 1 to 10
 * For multiples of 3, print "Fizz" instead of the number
 * For multiples of 5, print "Buzz" instead of the number
 * For multiples of both 3 and 5, print "FizzBuzz"
 */

function fizzBuzz(start = 1, end = 100) {
  for (let i = start; i <= end; i++) {
    if (i % 3 === 0 && i % 5 === 0) {
      console.log('FizzBuzz');
    } else if (i % 3 === 0) {
      console.log('Fizz');
    } else if (i % 5 === 0) {
      console.log('Buzz');
    } else {
      console.log(i);
    }
  }
}

// Run the FizzBuzz function for numbers 1-10
fizzBuzz(1, 10);

console.log('FizzBuzz completed!');