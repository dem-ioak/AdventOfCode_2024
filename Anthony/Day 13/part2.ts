import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let tokens = 0;
const cache = {};
for (const [_, ax, ay, bx, by, px, py] of input.matchAll(/Button A: X\+(\d+), Y\+(\d+)\r\nButton B: X\+(\d+), Y\+(\d+)\r\nPrize: X=(\d+), Y=(\d+)/gm)) {
	const aX = parseInt(ax);
	const aY = parseInt(ay);
	const bX = parseInt(bx);
	const bY = parseInt(by);
	const pX = parseInt(px) + 10000000000000;
	const pY = parseInt(py) + 10000000000000;

	/** Attempt 1 at doing relatively minor optimizations **/
	// let minCost = Infinity;
	// for (let a = 0; ; a++) {
	// 	let b = (pX - a * aX) / bX;
	// 	if (Number.isInteger(b) && a * aY + b * bY === pY) {
	// 		const cost = a * 3 + b;
	// 		if (cost < minCost) {
	// 			minCost = cost;
	// 		}
	// 	}
	// 	if (b < 1 || a * 3 > minCost) {
	// 		break;
	// 	}
	// }

	// Attempt 2: limit search to within one gcd of button a
	let minCost = Infinity;
	for (let a = Math.max(aX, aY); a >= 0; a--) {
		// try multiplying a as little as you can and still have a whole number b
		let aMult = 1;
		do {
			let b = (pX - (a * aMult * aX)) / bX;
			if (Number.isInteger(b) && a * aY + b * bY === pY) {
				const cost = a * aMult * 3 + b;
				if (cost < minCost) {
					minCost = cost;
				}
			}
			console.log("++", a, aMult, Math.floor(pX / aX), b, minCost)
			if (a === 0 || b < 1 || a * aMult * 3 > minCost) {
				break;
			}
			aMult++;
		} while (aMult < Math.max(bX, bY));

		// try multiplying a as high as you can and still have a whole number b
		aMult = Math.max(bX, bY);
		do {
			let b = (pX - a * aMult * aX) / bX;
			if (Number.isInteger(b) && a * aY + b * bY === pY) {
				const cost = a * aMult * 3 + b;
				if (cost < minCost) {
					minCost = cost;
				}
			}
			console.log("--", a, aMult, Math.floor(pX / aX), b)
			if (a === 0 || b < 1 || a * aMult * 3 > minCost) {
				break;
			}
			aMult--;
		} while (aMult > 1);
	}

	if (minCost != Infinity) {
		tokens += minCost;
	}
	console.log(aX, aY, bX, bY, pX, pY, minCost)
}

console.log(tokens);
