class AffineCipher {
  constructor(fn, chars) {
    this.fn = fn;
    this.chars = [];
    this.getIndex = {};
    this.getChar = {};

    for (let i = 0; i < chars.length; i++) {
      this.chars.push(chars[i]);
      this.getIndex[chars[i]] = i;
      this.getChar[String(i)] = chars[i];
    }

    // get/set the inverseFn:
    let num = this.fn(1) - Math.abs(this.fn(0));
    let modularInverse = (() => {
      let mod,
        inverse = 0;
      while (mod !== 1) {
        inverse++;
        mod = (inverse * num) % this.chars.length;
      }

      return inverse;
    })();

    this.inverseFn = (x) => modularInverse * (x - Math.abs(this.fn(0)));
  }

  getModularInverse = (num, moddedBy) => {
    let mod,
      inverse = 0;
    while (mod !== 1) {
      n++;
      mod = (n * num) % moddedBy;
    }

    return inverse;
  };

  encrypt = (message) => {
    let codes = message.split(" ");
    let res = [];

    for (let code of codes) {
      let resCode = "";
      for (let char of code) {
        let index = this.getIndex[char];
        let codedIndex = this.fn(index) % this.chars.length;
        let newChar = this.getChar[codedIndex];

        resCode += newChar;
      }
      res.push(resCode);
    }

    return res.join(" ");
  };

  decrypt = (codedMsg) => {
    let codes = codedMsg.split(" ");
    let res = [];

    for (let code of codes) {
      let resCode = "";
      for (let char of code) {
        let index = this.getIndex[char];
        let decodedIndex = this.inverseFn(index);
        while (decodedIndex < 0) {
          decodedIndex += this.chars.length;
        }
        decodedIndex = decodedIndex % this.chars.length;
        let newChar = this.getChar[decodedIndex];

        resCode += newChar;
      }
      res.push(resCode);
    }

    return res.join(" ");
  };
}

//////////////////////// MAIN /////////////////////////
const fn = (x) => 5 * x + 9;
const chars = [
  "A",
  "B",
  "C",
  "D",
  "E",
  "F",
  "G",
  "H",
  "I",
  "J",
  "K",
  "L",
  "M",
  "N",
  "O",
  "P",
  "Q",
  "R",
  "S",
  "T",
  "U",
  "V",
  "W",
  "X",
  "Y",
  "Z",
];

const cipher = new AffineCipher(fn, chars);

let msg = "TASTY MATH";
let codedMsg = cipher.encrypt("TASTY MATH");
let decodedMsg = cipher.decrypt(codedMsg);

console.log(msg + ",", codedMsg + ",", decodedMsg);
