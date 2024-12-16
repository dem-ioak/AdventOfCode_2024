import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let stones = input.trim().split(" ").map(stone => parseInt(stone));

for (let i = 0; i < 25; i++) {
	let newStones = [];
	stones.forEach(stone => {
		if (stone === 0) {
			newStones.push(1);
		} else if (`${stone}`.length % 2 === 0) {
			const newLength = `${stone}`.length / 2;
			newStones.push(parseInt(`${stone}`.slice(0, newLength)));
			newStones.push(parseInt(`${stone}`.slice(newLength)));
		} else {
			newStones.push(stone * 2024);
		}
	});
	stones = newStones;
	console.log(`iteration ${i + 1}: ${stones.join(" ")}`);
}

// Since this is an optimization problem, I'll mention this took 312 ms for me
console.log(stones.length);
