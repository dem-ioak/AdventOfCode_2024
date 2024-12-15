import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let tokens = 0;
for (const [_, ax, ay, bx, by, px, py] of input.matchAll(/Button A: X\+(\d+), Y\+(\d+)\r\nButton B: X\+(\d+), Y\+(\d+)\r\nPrize: X=(\d+), Y=(\d+)/gm)) {
	const aX = parseInt(ax);
	const aY = parseInt(ay);
	const bX = parseInt(bx);
	const bY = parseInt(by);
	const pX = parseInt(px);
	const pY = parseInt(py);
	let minCost = Infinity;
	for (let a = 0; a <= 100; a++) {
		for (let b = 0; b <= 100; b++) {
			const x = a * aX + b * bX;
			const y = a * aY + b * bY;
			if (x === pX && y === pY) {
				const cost = a * 3 + b;
				if (cost < minCost) {
					minCost = cost;
				}
			}
			if (x > pX || y > pY) {
				continue;
			}
		}
		if (a * aX > pX || a * aY > pY) {
			continue;
		}
	}
	if (minCost != Infinity) {
		tokens += minCost;
	}
	console.log(aX, aY, bX, bY, pX, pY, minCost)
}

console.log(tokens);
