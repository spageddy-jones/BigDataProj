"use strict";

let buttons = [];

function addButton(id, fn) {
    buttons.push({id: id, fn: fn});
}

function registerButtons() {
    buttons.forEach(button => {
        let el = document.getElementById(button.id);
        el.addEventListener("click", function() {
            this.disabled = true;
            button.fn();
            this.disabled = false;
        });
    });
}

addButton("ping-button", () => {
    let text = document.getElementById("ping-text").value;
    netCmd("ping", text, (res) => {
        document.getElementById("ping-output").value = res;
    });
});
