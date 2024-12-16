import fs from "fs";

const input = fs.readFileSync("input.txt").toString();

let map = input.trim().split("\r\n");

const Corner = {
	TopRight: 0,
	BottomRight: 1,
	BottomLeft: 2,
	TopLeft: 3
}

// Iterate through the map, and whenever we find a tile that's not part of a region, we know this is a tile that's on the outside perimeter of that region
// Traverse the region to find its area, and then start from that first tile to determine its perimeter:
//	the perimeter traversal stores which side(s) are part of the perimeter, and checking adjacent tiles to determine what side is being followed to get to the next tile in the perimeter
// Every visited tile will get marked as part of a region, so future traversals will ignore it

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
		if (map[row - 1]?.[col] != plantType) {
			perimeter++;
			localPerimeter++;
		}
		if (map[row + 1]?.[col] != plantType) {
			perimeter++;
			localPerimeter++;
		}
		if (map[row]?.[col - 1] != plantType) {
			perimeter++;
			localPerimeter++;
		}
		if (map[row]?.[col + 1] != plantType) {
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

	// We know the top and left sides of the first cell are part of the perimeter
	// Start at the topright corner, which will add the top side
	// and start perimeter at 1 to account for the left side
	// The exit condition is then when we traverse to the topleft of the starting cell
	// NVM, misread the Q and I thought it explicitly didn't want us to account for holes
	// let perimeter = 1;
	// function traversePerimeter(currRow, currCol, corner) {
	// 	// console.log(currRow, currCol, ["TopRight", "BottomRight", "BottomLeft", "TopLeft"][corner]);
	// 	if (currRow === row && currCol === col && corner === Corner.TopLeft) {
	// 		return;
	// 	}
	// 	perimeter++;
	// 	regionMap[currRow] = [...regionMap[currRow].slice(0, currCol), "#", ...regionMap[currRow].slice(currCol + 1)];
	// 	// Each corner can go in 1 of 3 directions based on whether certain cells are part of the region
	// 	if (corner === Corner.TopRight) {
	// 		if (region[currRow]?.[currCol + 1] && region[currRow - 1]?.[currCol + 1]) {
	// 			traversePerimeter(currRow - 1, currCol + 1, Corner.TopLeft);
	// 		} else if (region[currRow]?.[currCol + 1]) {
	// 			traversePerimeter(currRow, currCol + 1, Corner.TopRight);
	// 		} else {
	// 			traversePerimeter(currRow, currCol, Corner.BottomRight);
	// 		}
	// 	} else if (corner === Corner.BottomRight) {
	// 		if (region[currRow + 1]?.[currCol] && region[currRow + 1]?.[currCol + 1]) {
	// 			traversePerimeter(currRow + 1, currCol + 1, Corner.TopRight);
	// 		} else if (region[currRow + 1]?.[currCol]) {
	// 			traversePerimeter(currRow + 1, currCol, Corner.BottomRight);
	// 		} else {
	// 			traversePerimeter(currRow, currCol, Corner.BottomLeft);
	// 		}
	// 	} else if (corner === Corner.BottomLeft) {
	// 		if (region[currRow]?.[currCol - 1] && region[currRow + 1]?.[currCol - 1]) {
	// 			traversePerimeter(currRow + 1, currCol - 1, Corner.BottomRight);
	// 		} else if (region[currRow]?.[currCol - 1]) {
	// 			traversePerimeter(currRow, currCol - 1, Corner.BottomLeft);
	// 		} else {
	// 			traversePerimeter(currRow, currCol, Corner.TopLeft);
	// 		}
	// 	} else if (corner === Corner.TopLeft) {
	// 		if (region[currRow - 1]?.[currCol] && region[currRow - 1]?.[currCol - 1]) {
	// 			traversePerimeter(currRow - 1, currCol - 1, Corner.BottomLeft);
	// 		} else if (region[currRow - 1]?.[currCol]) {
	// 			traversePerimeter(currRow - 1, currCol, Corner.TopLeft);
	// 		} else {
	// 			traversePerimeter(currRow, currCol, Corner.TopRight);
	// 		}
	// 	}
	// }
	// traversePerimeter(row, col, Corner.TopRight);

	console.log(regionMap.map(r => r.join("")).join("\n"));
	console.log(`area:${area}\nperimeter:${perimeter}\ntotal:${area * perimeter}`);
	console.log("---");

	return area * perimeter;
}

console.log(sum);

// 2146650 too high
// 1431960 too low
// 1448494 too low
// 3517462
