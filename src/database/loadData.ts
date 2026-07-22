// @ts-ignore
import createModule from '../wasm/SatelliteCoverage.js';
import { loadTLE, getTLE } from "./db.js";

const groupNames = [
  "Earth Observation", "Communication", "Navigation", "Science & Research", "Miscellaneous"
]
let Module;
let allGroups;
let satelliteGroups;
let tSince;
let running = false;

async function start(t: number) {
    Module = await createModule();

    const arr = Module.getSatelliteGroups();
    allGroups = [];
    for (let i = 0; i < arr.size(); i++) {
        allGroups.push(arr.get(i));
    }
    arr.delete();

    satelliteGroups = allGroups.slice();
    tSince = t;

    for (const group of satelliteGroups) {
        await loadTLE(group);
        const data = await getTLE(group);
        Module.initializeSatelliteGroup(group, data);
    }
    
    filterTypes();
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

    self.postMessage({
        type: "update",
        data: data
        
    });

    setTimeout(updateLoop, 1000 / 60);
}

function filterType(group: string) {
    const result = Module.getSatelliteTypes(group);
    const nums = Module.getSatelliteTypeInts(group);
    const colour = Module.getSatelliteGroupColour(group);

    let total = 0;

    for (let i = 0; i < result.size(); i++) {
        total += nums.get(i);
    }

    let x = [];
    for (let i = 0; i < result.size(); i++) {
        const type = result.get(i);
        x.push([type, colour, total, nums.get(i), true, false]);
    }

    nums.delete();
    result.delete();

    return x;
}

function filterTypes() {
    const filter = new Map();

    groupNames.forEach(name => {
        filter.set(name, filterType(name));
    })

    self.postMessage({
        type: "filter",
        data: filter
    });
}

function updateGroups(groups) {
    let i = 0;

    satelliteGroups.length = 0;
    groupNames.forEach(name => {
        const groupTypes = groups.get(name);
        groupTypes.forEach(type => {
            if (type[4]) {
                satelliteGroups.push(allGroups[i])
            };
            i++;
        });
    });
}

function getSatellite(index: number) 
{
    let start = 0;
    for (const group of satelliteGroups)
    {
        const count = Module.getSatellitesNum(group);

        if (index < start + count) {
            const localIndex = index - start;

            const sat = Module.getSpecificSatellite(group, localIndex, tSince);

            self.postMessage({
                type: "getSatellite",
                satellite: sat
            })

            return;
        }

        start += count;
    }
}

self.onmessage = async (event) => {
    if (event.data.type === "start") {
        await start(event.data.tSince);
    }

    if (event.data.type === "getSatellite") {
        getSatellite(event.data.index);
    }

    if (event.data.type === "updateGroups") {
        updateGroups(event.data.groups);
    }

    if (event.data.type == "setTimeRate") {
        tSince = event.data.tSince;
    }

    if (event.data.type === "stop") {
        running = false;
    }
};
