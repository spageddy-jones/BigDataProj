"use strict";

let statusEl = null;

function setStatus(msg) {
    statusEl = document.getElementById("status");

    if (statusEl === null) {
        console.log("Error: unable to find statusEl");
        console.log(`Intended message was: ${msg}`);
        return;
    } else {
        statusEl.innerText = msg;
    }
}
