import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

const stones = input.trim().split(" ").map(stone => parseInt(stone));

const cache = {};
function numStones(stone, iterations) {
	if (iterations === 0) {
		return 1;
	}
	if (cache[stone]?.[iterations]) {
		return cache[stone][iterations];
	}
	cache[stone] ??= {};
	if (stone === 0) {
		cache[stone][iterations] = numStones(1, iterations - 1);
		return cache[stone][iterations];
	}
	const stoneString = `${stone}`;
	if (stoneString.length % 2 === 0) {
		cache[stone][iterations] =
			numStones(parseInt(stoneString.slice(0, stoneString.length / 2)), iterations - 1) +
			numStones(parseInt(stoneString.slice(stoneString.length / 2)), iterations - 1);
		return cache[stone][iterations];
	}
	cache[stone][iterations] = numStones(stone * 2024, iterations - 1);
	return cache[stone][iterations];
}

const sum = stones.reduce((acc, curr) => acc + numStones(curr, 75), 0);
// 180 ms!
console.log(sum);
