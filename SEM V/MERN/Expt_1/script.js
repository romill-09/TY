// Array Methods
var arr = [1, 5, 3, 6, 2];

console.log("Intial Array order: " + arr);
const sortArr = () => {
  if (arr.length === 0) {
    throw new Error("Array is empty");
  } else {
    for (let i = 0; i < arr.length; i++) {
      for (let j = 0; j < arr.length - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
          let temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
        }
      }
    }
  }
  console.log("Sorted Array: " + arr);
};

const reverseArr = () => {
  var temp = [];

  for (let i = 0; i < arr.length; i++) {
    temp[i] = arr[arr.length - 1 - i];
  }

  console.log("Reversed Array: " + temp);
};

const maxEl = () => {
  let mx = -Infinity;
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] > mx) {
      mx = arr[i];
    }
  }

  console.log("Max Element: " + mx);
};

// Date Methods
const todaysDate = new Date();
console.log("Current Date: " + todaysDate);

const getCurrentDateTime = () => {
  const now = new Date();
  console.log("Current Date and Time:", now.toLocaleString());
};

const daysBetweenDates = () => {
  const date1 = "2024-07-01";
  const date2 = "2024-07-21";

  console.log("date1: " + date1 + " date2: " + date2);
  const oneDay = 24 * 60 * 60 * 1000;
  const firstDate = new Date(date1);
  const secondDate = new Date(date2);

  if (isNaN(firstDate) || isNaN(secondDate)) {
    console.error("Invalid date format");
    return;
  }

  const diffDays = Math.round(Math.abs((firstDate - secondDate) / oneDay));
  console.log("Days Between Dates:", diffDays);
};

const addDaysToDate = () => {
  const initialDate = new Date();
  const daysToAdd = 10;
  const resultDate = new Date(initialDate);

  if (isNaN(resultDate)) {
    console.error("Invalid date format");
    return;
  }

  resultDate.setDate(resultDate.getDate() + daysToAdd);
  console.log("New Date After Adding Days:", resultDate.toLocaleDateString());
};

//String Methods
const str = "Hello, World!";
console.log("Initial String: " + str);

const reverseString = () => {
  const str = "Hello, World!";

  if (typeof str !== "string") {
    throw new Error("Input should be a string");
  }

  const res = str.split("").reverse().join("");

  console.log("Reversed String: " + res);
};

const upperCase = () => {
  const str = "Hello, World!";
  const res = str.toUpperCase();

  console.log("String in upper case: " + res);
};

const slicedString = () => {
  const str = "Hello, World!";
  const res = str.slice(0, 5);

  console.log("Sliced String: " + res);
};

// Browser Specific Code
const detectBrowser = () => 
  {
    const userAgent = navigator.userAgent;
  
    if (userAgent.includes("Firefox")) 
    {
      console.log("You are using Mozilla Firefox.");
    } 
    else if (userAgent.includes("Edg/")) 
    {
      console.log("You are using Microsoft Edge.");
    } 
    else if (userAgent.includes("Chrome") && !userAgent.includes("Edg/")) 
    {
      console.log("You are using Google Chrome.");
    } 
    else if (userAgent.includes("Safari") && !userAgent.includes("Chrome") && !userAgent.includes("Edg/")) 
    {
      console.log("You are using Safari.");
    } 
    else if (userAgent.includes("MSIE") || userAgent.includes("Trident")) 
    {
      console.log("You are using Internet Explorer.");
    } 
    else 
    {
      console.log("Browser not detected or unknown.");
    }
  };
  