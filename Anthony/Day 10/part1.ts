import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

const topoMap = input.trim().split("\r\n");
const solvedTiles = new Array(topoMap.length).fill(0).map(_ => new Array(topoMap[0].length).fill(null));

let sum = 0;

// Look for trailheads and search for paths to 9s.
// If a tile is >=0 in solvedTiles then its number is equivalent to the number of trailheads that positions can get to
// That check will remove redundant path traversals
for (let row = 0; row < topoMap.length; row++) {
	for (let col = 0; col < topoMap[row].length; col++) {
		if (topoMap[row][col] === "0") {
			sum += traverse(row, col).size;
		}
	}
}

function traverse(row, col) {
	if (topoMap[row][col] === "9") {
		return new Set([hashPos(row, col)]);
	}
	if (solvedTiles[row][col] != null) {
		return solvedTiles[row][col];
	}
	let ends = new Set();
	let currScore = parseInt(topoMap[row][col]);
	if (topoMap[row - 1]?.[col] == currScore + 1) {
		ends = ends.union(traverse(row - 1, col));
	}
	if (topoMap[row + 1]?.[col] == currScore + 1) {
		ends = ends.union(traverse(row + 1, col));
	}
	if (topoMap[row][col - 1] == currScore + 1) {
		ends = ends.union(traverse(row, col - 1));
	}
	if (topoMap[row][col + 1] == currScore + 1) {
		ends = ends.union(traverse(row, col + 1));
	}
	console.log(row, col, ends)
	solvedTiles[row][col] = ends;
	return ends;
}

function hashPos(row, col) {
	// shut up this is fine for this
	return row * 1000 + col;
}

console.log(solvedTiles.map((r, row) => [...r].map((c, col) => topoMap[row][col] === "9" ? "X" : c == null ? "." : topoMap[row][col] === "0" ? "#" : c.size).join("")).join("\n"));
console.log(sum);
