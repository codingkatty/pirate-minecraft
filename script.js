async function generateMap() {
    const seed = document.getElementById("seedInput").value || 0;
    const response = await fetch(`http://localhost:5000/generate?seed=${seed}`);
    const data = await response.json();
    
    const map = document.getElementById("map");
    map.innerHTML = ""; // Clear map

    // Render shipwrecks
    data.shipwrecks.forEach(shipwreck => {
        const cell = document.createElement("div");
        cell.className = "cell marker-shipwreck";
        cell.style.gridColumnStart = shipwreck.x;
        cell.style.gridRowStart = shipwreck.z;
        map.appendChild(cell);
    });

    // Render treasures
    data.treasures.forEach(treasure => {
        const cell = document.createElement("div");
        cell.className = "cell marker-treasure";
        cell.style.gridColumnStart = treasure.x;
        cell.style.gridRowStart = treasure.z;
        map.appendChild(cell);
    });
}