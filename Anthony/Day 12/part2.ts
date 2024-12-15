import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let map = input.trim().split("\r\n");

const visited = {};
let sum = 0;
for (let row = 0; row < map.length; row++) {
	for (let col = 0; col < map[row].length; col++) {
		if (visited[row]?.[col] == null) {
			sum += calculateCost(row, col);
		}
	}
}

function calculateCost(row, col) {
	const plantType = map[row][col];
	console.log(row, col, plantType)
	const region = {};
	let area = 0;
	let perimeter = 0;
	const regionMap = new Array(map.length).fill(0).map(() => new Array(map[0].length).fill("."));
	function traverse(row, col) {
		if (region[row]?.[col] != null || map[row]?.[col] !== plantType) {
			return;
		}
		region[row] ??= {};
		region[row][col] = true;
		visited[row] ??= {};
		visited[row][col] = true;
		area++;

		// Update perimeter
		let localPerimeter = 0;
		// For each, check if this isn't extending a side from above or to the left
		// So each side should just have the cell closest to the top left count
		// Up
		if (map[row - 1]?.[col] != plantType && (map[row]?.[col - 1] != plantType || map[row - 1]?.[col - 1] == plantType)) {
			perimeter++;
			localPerimeter++;
		}
		// Down
		if (map[row + 1]?.[col] != plantType && (map[row]?.[col - 1] != plantType || map[row + 1]?.[col - 1] == plantType)) {
			perimeter++;
			localPerimeter++;
		}
		// Left
		if (map[row]?.[col - 1] != plantType && (map[row - 1]?.[col] != plantType || map[row - 1]?.[col - 1] == plantType)) {
			perimeter++;
			localPerimeter++;
		}
		// Right
		if (map[row]?.[col + 1] != plantType && (map[row - 1]?.[col] != plantType || map[row - 1]?.[col + 1] == plantType)) {
			perimeter++;
			localPerimeter++;
		}
		regionMap[row] = [...regionMap[row].slice(0, col), localPerimeter, ...regionMap[row].slice(col + 1)];

		traverse(row - 1, col);
		traverse(row + 1, col);
		traverse(row, col - 1);
		traverse(row, col + 1);
	}
	traverse(row, col);

	console.log(regionMap.map(r => r.join("")).join("\n"));
	console.log(`area:${area}\nperimeter:${perimeter}\ntotal:${area * perimeter}`);
	console.log("---");

	return area * perimeter;
}

console.log(sum);
