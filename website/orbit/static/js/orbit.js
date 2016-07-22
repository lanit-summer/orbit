var container;
var camera, scene, renderer;
var earth;
var ship;
var moon;
var boost = 1; //ускорение
var prevBoost = 1; //нужно для stop
var paused = false;
var mouseDown = 0;
var loader;
var pivot;
var speedArray;
var posArray;

const EARTH_TEX = "../../static/img/land_ocean_ice_cloud_2048.jpg";
const STARS_TEX = "../../static/img/maxresdefault.jpg";
const MOON_TEX = "../../static/img/Moon.jpg";

const EARTH_PH_MAT = new THREE.MeshPhongMaterial({
    map: THREE.ImageUtils.loadTexture(EARTH_TEX),
    overdraw: 1
});
const EARTH_BAS_MAT = new THREE.MeshBasicMaterial({
    map: THREE.ImageUtils.loadTexture(EARTH_TEX)
});
const MOON_PH_MAT = new THREE.MeshPhongMaterial({
    map: THREE.ImageUtils.loadTexture(MOON_TEX),
    overdraw: 1
});
const MOON_BAS_MAT = new THREE.MeshBasicMaterial({
    map: THREE.ImageUtils.loadTexture(MOON_TEX)
});

document.addEventListener('DOMContentLoaded', function () {
    loadSampleOrbit();
    init();
    animate();
}, false);

function init() {
    var trajectory = document.getElementById("trajectory").value;
    if (trajectory) {
        loadOrbitFromCalculator(trajectory);
    }

    start();
    controlSpeed();
    changeView();

    renderer = Detector.webgl ? new THREE.WebGLRenderer() : new THREE.CanvasRenderer();
    container = document.getElementById('scene');
    camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 1, 200000000);
    scene = new THREE.Scene();

    if (Detector.webgl)
        addLights();
    
    loadEarth();
    loadMoon();
    loadShip();
    loadStars();

	pivot = new THREE.Object3D();
    scene.add(pivot);
    pivot.add(moon);
    
    camera.position.z = 13371;

    var canvas = document.createElement('canvas');
    canvas.width = 128;
    canvas.height = 128;
    var context = canvas.getContext('2d');
    context.fillRect(0, 0, canvas.width, canvas.height);

    renderer.setClearColor(0x000000, 1);
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.setSize(window.innerWidth, window.innerHeight - 70);
    container.appendChild(renderer.domElement);

    window.addEventListener('resize', onWindowResize, false);
    controls = new THREE.OrbitControls(camera, renderer.domElement);
    controls.target = earth.position;
    restart();
}

function controlSpeed() {
    document.getElementById("increase").onclick = function () {
        if (!paused) {
            increaseBoost();
            renewBoostSign();
        }
    }

    document.getElementById("decrease").onclick = function () {
        if (!paused) {
            decreaseBoost();
            renewBoostSign();
        }
    }

    document.getElementById("play").onclick = function () {
        if (paused)
            playBoost();
    }

    document.getElementById("stop").onclick = function () {
        if (!paused) {
            stopBoost();
        }
    }

    document.getElementById("restart").onclick = function () {
        restart();
    }
}

function changeView() {
    document.getElementById("lookAt").onchange = function () {
        if (this.value == "moon") {
            controls.target = moon.position;
            camera.lookAt(moon);
        }
        if (this.value == "earth") {
            controls.target = earth.position;
            camera.lookAt(earth);
        }
        if (this.value == "satelite") {
            controls.target = ship.position;
            camera.lookAt(ship);
        }
    }
}

function loadStars() {
    loader = new THREE.TextureLoader();
    var texture = loader.load(STARS_TEX);
    var backgroundMesh = new THREE.Mesh(
        new THREE.PlaneGeometry(2, 2, 0),
        new THREE.MeshBasicMaterial({
            map: texture
        }));
    backgroundMesh.material.depthTest = false;
    backgroundMesh.material.depthWrite = false;

    var backgroundScene = new THREE.Scene();
    var backgroundCamera = new THREE.Camera();
    backgroundScene.add(backgroundCamera);
    backgroundScene.add(backgroundMesh);

    var renderStar = function () {
        requestAnimationFrame(renderStar);
        renderer.autoClear = false;
        renderer.clear();
        renderer.render(backgroundScene, backgroundCamera);
    };

    renderStar();
}

function loadEarth() {
    var geometry = new THREE.SphereGeometry(6371, 50, 50);
    earth = Detector.webgl ? new THREE.Mesh(geometry, EARTH_PH_MAT) : new THREE.Mesh(geometry, EARTH_BAS_MAT);
    scene.add(earth);
}

function loadMoon() {
    var geometry = new THREE.SphereGeometry(1737, 30, 30);
    moon = Detector.webgl ? new THREE.Mesh(geometry, MOON_PH_MAT) : new THREE.Mesh(geometry, MOON_BAS_MAT);
    scene.add(moon);
    moon.position.set(-160000, 0, 0);
}

function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

function renewBoostSign() {
    document.getElementById("currentBoost").innerHTML = "x" + boost;
}

function increaseBoost() {
    if (boost < 1000)
        boost *= 2;
}

function decreaseBoost() {
    if (boost > 0)
        boost = Math.ceil(boost / 2);
}

function stopBoost() {
    if (boost != 0)
        prevBoost = boost;
    boost = 0;
    paused = true;
}

function playBoost() {
    paused = false;
    boost = prevBoost;
}

function animate() {
    requestAnimationFrame(animate);
    render();
    controls.update();
}

function render() {
    updateShipOrbit();
    updateEarthRotation();
    updateMoonOrbitRotation();
    renderer.render(scene, camera);
}

function updateMoonOrbitRotation() {
    pivot.rotation.y += 0.002;
}

function addLights() {
    var dirLight = new THREE.DirectionalLight(0xffffff, 1);
    dirLight.position.set(-200000, 0, 0);
    scene.add(dirLight);

    var spotLight = new THREE.SpotLight(0xffffff, 0.7, 200000, 180, 0);
    spotLight.position.set(0, 0, 0);
    var spotTarget = new THREE.Object3D();
    spotTarget.position.set(-160000, 0, 0);
    spotLight.target = spotTarget;

    scene.add(spotLight);
}

function loadShip() {
    var loader = new THREE.ObjectLoader();
    loader.load('../../static/js/ship.json', function (obj) {
        ship = obj;
        var xpos = posArray[0][0];
        var ypos = posArray[0][2];
        var zpos = posArray[0][1];
        ship.scale.set(15, 15, 15);
        ship.position.set(xpos, ypos, zpos);
        scene.add(ship);
    });
}

function updateShipOrbit() {
    if (total_seconds > posArray.length - 1) {
        alert("Симуляция закончена");
        restart();
    }
    var xpos = posArray[total_seconds][0];
    var ypos = posArray[total_seconds][2];
    var zpos = posArray[total_seconds][1];

    var curMill = (total_seconds + 1) * 1000 - total_milliseconds;
    xpos += curMill / 1000 * speedArray[total_seconds][0];
    ypos += curMill / 1000 * speedArray[total_seconds][2];
    zpos += curMill / 1000 * speedArray[total_seconds][1];
    document.getElementById("pos_x").innerHTML = xpos.toFixed(2);
    document.getElementById("pos_y").innerHTML = ypos.toFixed(2);
    document.getElementById("pos_z").innerHTML = zpos.toFixed(2);

    document.getElementById("speed_x").innerHTML = speedArray[total_seconds][0].toFixed(2);
    document.getElementById("speed_y").innerHTML = speedArray[total_seconds][2].toFixed(2);
    document.getElementById("speed_z").innerHTML = speedArray[total_seconds][1].toFixed(2);

    ship.position.set(xpos, ypos, zpos);
}

function updateEarthRotation() {
    earth.rotation.y = -total_milliseconds * 0.000000072921158553;
}

function sunTurnOn() {
    if (Detector.webgl) {
        earth.material = EARTH_PH_MAT;
        moon.material = MOON_PH_MAT;
    }
}

function sunTurnOff() {
    if (Detector.webgl) {
        earth.material = EARTH_BAS_MAT;
        moon.material = MOON_BAS_MAT;
    }
}

function loadSampleOrbit() {
    var xhr;
    if (window.XMLHttpRequest) {
        xhr = new XMLHttpRequest();
    } else if (window.ActiveXObject) {
        xhr = new ActiveXObject("Microsoft.XMLHTTP");
    }

    xhr.onreadystatechange = function () {
        var arr = xhr.responseText.split('\n');
        if (arr.length != 1) {
            posArray = new Array(arr.length);
            speedArray = new Array(arr.length);
            for (var i = 0; i < arr.length - 1; i++) {
                var line = arr[i].split(' ');

                var position = new Array(3);
                position[0] = parseInt(line[1]);
                position[1] = parseInt(line[2]);
                position[2] = parseInt(line[3]);
                posArray[i] = position;

                speed = new Array(3);
                speed[0] = parseInt(line[4]);
                speed[1] = parseInt(line[5]);
                speed[2] = parseInt(line[6]);

                speedArray[i] = speed;
            }
            boost = Math.ceil(posArray.length / 180);
            renewBoostSign();
        }
    };
    xhr.open("GET", "../../static/js/orbit.xyzv", false);
    xhr.send();
}

//TODO Duplicate code

function loadOrbitFromCalculator(text) {
    var arr = text.split('\n');
    if (arr.length != 1) {
        posArray = new Array(arr.length);
        speedArray = new Array(arr.length);
        for (var i = 0; i < arr.length - 1; i++) {
            var line = arr[i].split(' ');

            var position = new Array(3);
            position[0] = parseInt(line[1]);
            position[1] = parseInt(line[2]);
            position[2] = parseInt(line[3]);
            posArray[i] = position;

            speed = new Array(3);
            speed[0] = parseInt(line[4]);
            speed[1] = parseInt(line[5]);
            speed[2] = parseInt(line[6]);
            speedArray[i] = speed;
        }
        boost = Math.ceil(posArray.length / 180);
        renewBoostSign();
    }
}

function restart() {
    stopBoost();
    total_seconds = 0;
    total_milliseconds = 0;
}