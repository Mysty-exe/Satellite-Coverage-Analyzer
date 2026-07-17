// @ts-ignore
import createModule from '../wasm/SatelliteCoverage.js';
import { loadTLE, getTLE } from "./db.js";

let Module;
let satelliteGroups;
let tSince;
let running = false;

async function start(groups: string[], t: number) {
    Module = await createModule();
    satelliteGroups = groups;
    tSince = t;

    for (const group of satelliteGroups) {
        await loadTLE(group);
        const data = await getTLE(group);
        Module.initializeSatelliteGroup(group, data);
    }
    
    running = true;
    updateLoop();
}

function updateLoop() {
    if (!running) return;

    const data = [];
    for (const group of satelliteGroups)
    {
        const satellites = Module.getSatellitesDTO(group, tSince);

        for (let i = 0; i < satellites.size(); i++) {
            const sat = satellites.get(i);

            data.push({
                name: sat.name,
                colour: sat.colour,
                lat: sat.lat,
                lon: sat.lon,
                alt: sat.alt
            });
        }

    satellites.delete();
    }

    self.postMessage(data);

    setTimeout(updateLoop, 1000 / 60);
}

self.onmessage = async (event) => {
    if (event.data.type === "start") {
        await start(event.data.groups, event.data.tSince);
    }

    if (event.data.type == "setTimeRate") {
        tSince = event.data.tSince;
    }

    if (event.data.type === "stop") {
        running = false;
    }
};