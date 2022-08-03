"use strict";

const pingInterval = 500;
const timeout = 1000;

let ping = null;

let pingList = [];

function makeRequest(url, method, fn, value) {
    let xhr = new XMLHttpRequest();

    xhr.timeout = timeout;
    xhr.open(method, url);

    xhr.onload = () => {
        if (xhr.status == 200)
        {
            setStatus("Connected", "darkgreen");
            fn(xhr.responseText);
        } else {
            setStatus("Connection lost", "darkred");
        }
    };

    xhr.ontimeout = () => {
        setStatus("Connection lost", "darkred");
    };

    xhr.send(value);
}

function netCmd(name, value, fn) {
    makeRequest(`/cmd/${name}`, "POST", fn, value);
}

function netValue(name, fn) {
    makeRequest(`/value/${name}`, "GET", fn);
}

function netStartPingLoop() {
    netValue("ping", () => {});

    ping = setInterval(() => {
        pingList.forEach(fn => fn());
    }, pingInterval);
}

function netAddToPingList(fn) {
    pingList.push(fn);
}
