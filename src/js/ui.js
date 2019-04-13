// "use strict";

const ui = (()=>{
	const canvas = document.getElementById("ui");
	const ctx = canvas.getContext("2d");
	ctx.rem = parseFloat(getComputedStyle(document.documentElement).fontSize);
	return ctx;
})();

function setHP(hp) {
	const w = ui.canvas.width;
	const h = ui.canvas.height;
	const rem = ui.rem;
	ui.clearRect(0, h - rem * 2, w / 3, rem * 2);
	ui.fillStyle = "rgba(20,20,20, 0.5)";
	ui.fillRect(0, h - rem * 2, w / 3, rem * 2);
	ui.fillStyle = "rgba(240,30,30, 0.6)";
	ui.fillRect(0, h - rem * 1.8, (w / 300) * hp, rem * 1.4);
}