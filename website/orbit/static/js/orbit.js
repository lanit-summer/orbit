var container;
var camera, scene, renderer;
var earth;
var ship;
var mouseX = 0, mouseY = 0;
var boost = 1; //ускорение
var prevBoost = 1; //нужно для stop
var paused = false;
var mouseDown = 0;
var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;
var cube;
var moon;

var speedArray;
var posArray;

document.addEventListener('DOMContentLoaded', function() {
    loadSampleOrbit();
    init();
    animate();
}, false);

function init() {
    restart();
    var trajectory = document.getElementById("trajectory").value;
    if (trajectory) {
        loadOrbitFromCalculator(trajectory);
    }
    start();
    document.onmousedown = function() {
        ++mouseDown;
    }
    document.onmouseup = function() {
        --mouseDown;
    }

    document.getElementById("increase").onclick = function(){
        if (!paused) {
            increaseBoost();
            renewBoostSign();
        }
    }

    document.getElementById("decrease").onclick = function(){
        if (!paused) {
            decreaseBoost();
            renewBoostSign();
        }
    }

    document.getElementById("play").onclick = function(){
        if (paused)
            playBoost();
    }

    document.getElementById("stop").onclick = function(){
        if (!paused) {
            stopBoost();
        }
    }

    document.getElementById("restart").onclick = function(){
        restart();
    }

    document.getElementById("lookAt").onchange = function(){
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

    renderer = Detector.webgl? new THREE.WebGLRenderer(): new THREE.CanvasRenderer();
	var loader = new THREE.TextureLoader();

	var texture = loader.load( "../../static/img/maxresdefault.jpg" );
    var backgroundMesh = new THREE.Mesh(
        new THREE.PlaneGeometry(2, 2, 0),
        new THREE.MeshBasicMaterial({
            map: texture
        }));
	backgroundMesh.material.depthTest = false;
    backgroundMesh.material.depthWrite = false;

    
    var backgroundScene = new THREE.Scene();
    var backgroundCamera = new THREE.Camera();
    backgroundScene.add(backgroundCamera );
    backgroundScene.add(backgroundMesh );
	

	var texture = THREE.ImageUtils.loadTexture( '../../static/img/maxresdefault.jpg' );
        var backgroundMesh = new THREE.Mesh(
            new THREE.PlaneGeometry(2, 2, 0),
            new THREE.MeshBasicMaterial({
                map: texture
            }));
			
	backgroundMesh.material.depthTest = false;
    backgroundMesh.material.depthWrite = false;
		
	var backgroundScene = new THREE.Scene();
    var backgroundCamera = new THREE.Camera();
    backgroundScene.add(backgroundCamera );
    backgroundScene.add(backgroundMesh );
	
	
	var renderStar = function () {
        requestAnimationFrame(renderStar);
        renderer.autoClear = false;
        renderer.clear();
        renderer.render(backgroundScene , backgroundCamera );
    };
	
	renderStar();

    container = document.getElementById('scene');
    camera = new THREE.PerspectiveCamera( 60, window.innerWidth / window.innerHeight, 1, 200000000);

    scene = new THREE.Scene();
    earth = new THREE.Group();
    
    addLights();
    
    scene.add(earth);
    // earth
    var loader = new THREE.TextureLoader();
    var imgurl = "../../static/img/land_ocean_ice_cloud_2048.jpg";
    loader.load(imgurl, function (texture) { 
                    var geometry = new THREE.SphereGeometry(6371, 50, 50);
                    var material = new THREE.MeshPhongMaterial({ map: texture, overdraw: 0.5 });
                    var mesh = new THREE.Mesh(geometry, material);
                    earth.add(mesh);
    } );

    moon = new THREE.Group();
    scene.add(moon);
    
    var loader = new THREE.TextureLoader();
    var imgurl = "../../static/img/Moon.jpg"
    loader.load(imgurl, function (texture) { 
                    var geometry = new THREE.SphereGeometry(1737, 30, 30);
                    var material = new THREE.MeshPhongMaterial({ map: texture, overdraw: 0.5 });
                    var mesh = new THREE.Mesh(geometry, material);
                    moon.add(mesh);
    });
    moon.position.set(-160000, 0, 0);

    loadShip();
    
    camera.position.z = 13371;
    var canvas = document.createElement( 'canvas' );
    canvas.width = 128;
    canvas.height = 128;
    var context = canvas.getContext('2d');
    context.fillRect( 0, 0, canvas.width, canvas.height );

    renderer.setClearColor(0x000000, 1);
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize( window.innerWidth, window.innerHeight - 70);
    container.appendChild( renderer.domElement );

    window.addEventListener('resize', onWindowResize, false );
    controls = new THREE.OrbitControls(camera, renderer.domElement);
    controls.target = earth.position;
}

function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

function renewBoostSign() {
    document.getElementById("currentBoost").innerHTML="x"+boost;
}

function increaseBoost() {
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
    renderer.render(scene, camera);
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
    ship = new THREE.Group();
    var geometry = new THREE.BoxGeometry( 100, 100, 100 );
    var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
    cube = new THREE.Mesh( geometry, material );
    ship.add(cube);
    var xpos = posArray[0][0];
    var ypos = posArray[0][2];
    var zpos = posArray[0][1];
    ship.position.set(xpos, ypos, zpos);
    scene.add(ship);
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

function loadSampleOrbit() {
    var xhr;
    if (window.XMLHttpRequest) {
        xhr = new XMLHttpRequest();
    } else if (window.ActiveXObject) {
        xhr = new ActiveXObject("Microsoft.XMLHTTP");
    }

    xhr.onreadystatechange = function(){
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
    xhr.open("GET","../../static/js/orbit.xyzv", false);
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