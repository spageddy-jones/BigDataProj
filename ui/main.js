"use strict";

window.addEventListener("load", () => {
    setStatus("Initializing...");
    registerButtons();
    netStartPingLoop();
});
