import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

const topoMap = input.trim().split("\r\n");
const solvedTiles = new Array(topoMap.length).fill(0).map(_ => new Array(topoMap[0].length).fill(null));

let sum = 0;

// Ha, this is something I'd "solved" earler in part 1

for (let row = 0; row < topoMap.length; row++) {
	for (let col = 0; col < topoMap[row].length; col++) {
		if (topoMap[row][col] === "0") {
			sum += traverse(row, col);
		}
	}
}

function traverse(row, col) {
	if (topoMap[row][col] === "9") {
		return 1;
	}
	if (solvedTiles[row][col] != null) {
		return solvedTiles[row][col];
	}
	let ends = 0;
	let currScore = parseInt(topoMap[row][col]);
	if (topoMap[row - 1]?.[col] == currScore + 1) {
		ends += traverse(row - 1, col);
	}
	if (topoMap[row + 1]?.[col] == currScore + 1) {
		ends += traverse(row + 1, col);
	}
	if (topoMap[row][col - 1] == currScore + 1) {
		ends += traverse(row, col - 1);
	}
	if (topoMap[row][col + 1] == currScore + 1) {
		ends += traverse(row, col + 1);
	}
	console.log(row, col, ends)
	solvedTiles[row][col] = ends;
	return ends;
}

function hashPos(row, col) {
	// shut up this is fine for this
	return row * 1000 + col;
}

console.log(solvedTiles.map((r, row) => [...r].map((c, col) => topoMap[row][col] === "9" ? "X" : c == null ? "." : topoMap[row][col] === "0" ? "#" : "+").join("")).join("\n"));
console.log(sum);
