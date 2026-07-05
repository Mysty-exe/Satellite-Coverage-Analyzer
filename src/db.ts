import { openDB } from "idb";

export const db = await openDB("SatelliteCoverage", 1, {
  upgrade(db) {
    db.createObjectStore("tle");
  },
});

async function getTLE(group: string) {
    const cached = await db.get("tle", group);

    if (
        cached &&
        Date.now() - cached.downloadedAt < 2 * 60 * 60 * 1000
    ) {
        return cached.data;
    }

    const response = await fetch(
        `https://celestrak.org/NORAD/elements/gp.php?GROUP=${group}&FORMAT=tle`
    );

    if (response.status == 403)
        return cached.data;

    const text = await response.text();

    await db.put(
        "tle",
        {
            data: text,
            downloadedAt: Date.now(),
        },
        group
    );

    return text;
}

export default getTLE
