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
    var trajectory = document.getElementById("trajectory").value;
    if (trajectory) {
        loadOrbitFromCalculator(trajectory);
    }
    start();
    console.log(posArray.length);
    document.onmousedown = function() {
        ++mouseDown;
    }
    document.onmouseup = function() {
        --mouseDown;
    }

    document.getElementById("increase").onclick = function(){
        if (!paused) {
            inrecaseBoost();
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

    container = document.getElementById('scene');
    camera = new THREE.PerspectiveCamera( 60, window.innerWidth / window.innerHeight, 1, 200000000);

    scene = new THREE.Scene();
    earth = new THREE.Group();
    
    scene.add(earth);
    // earth
    var loader = new THREE.TextureLoader();
    //FIXME
    var imgurl = "../../static/img/land_ocean_ice_cloud_2048.jpg";
    loader.load(imgurl, function (texture) { 
                    var geometry = new THREE.SphereGeometry(6371, 30, 30);
                    var material = new THREE.MeshBasicMaterial({ map: texture, overdraw: 0.5 });
                    var mesh = new THREE.Mesh(geometry, material);
                    earth.add(mesh);
    } );

    moon = new THREE.Group();
    scene.add(moon);
    var loader = new THREE.TextureLoader();
    var imgurl = "../../static/img/Moon.jpg"
    loader.load(imgurl, function (texture) { 
                    var geometry = new THREE.SphereGeometry(1737, 30, 30);
                    var material = new THREE.MeshBasicMaterial({ map: texture, overdraw: 0.5 });
                    var mesh = new THREE.Mesh(geometry, material);
                    moon.add(mesh);
    });
    moon.position.set(-32000, 0, 0);

    loadShip();
    
    camera.position.z = 13371;
    var canvas = document.createElement( 'canvas' );
    canvas.width = 128;
    canvas.height = 128;
    var context = canvas.getContext('2d');
    context.fillRect( 0, 0, canvas.width, canvas.height );

    renderer = new THREE.CanvasRenderer();
    renderer.setClearColor(0x000000, 1);
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize( window.innerWidth, window.innerHeight - 70);
    container.appendChild( renderer.domElement );
    
    //document.addEventListener('mousemove', onDocumentMouseMove, false );
    //document.addEventListener('mousewheel', mousewheel, false );
    //document.addEventListener('DOMMouseScroll', mousewheel, false ); // firefox
    window.addEventListener('resize', onWindowResize, false );
    
    controls = new THREE.OrbitControls(camera, renderer.domElement);
    controls.target = new THREE.Vector3(0, 100, 0);
}

function onWindowResize() {
    windowHalfX = window.innerWidth / 2;
    windowHalfY = window.innerHeight / 2;
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize( window.innerWidth, window.innerHeight );
}

function renewBoostSign() {
    document.getElementById("currentBoost").innerHTML="x"+boost;
}

function mousewheel( e ) {      
    var d = ((typeof e.wheelDelta != "undefined")?(-e.wheelDelta):e.detail);
    d = 100 * ((d>0)?1:-1);

    var cPos = camera.position;
    if (isNaN(cPos.x) || isNaN(cPos.y) || isNaN(cPos.y))
      return;

    var r = cPos.x * cPos.x + cPos.y * cPos.y;
    var sqr = Math.sqrt(r);
    var sqrZ = Math.sqrt(cPos.z * cPos.z + r);


    var nx = cPos.x + ((r==0)?0:(d * cPos.x/sqr));
    var ny = cPos.y + ((r==0)?0:(d * cPos.y/sqr));
    var nz = cPos.z + ((sqrZ==0)?0:(d * cPos.z/sqrZ));


    if (Math.sqrt(nx*nx + ny*ny + nz*nz) < 300)
        return; 

    if (isNaN(nx) || isNaN(ny) || isNaN(nz))
      return;

    cPos.x = nx;
    cPos.y = ny;
    cPos.z = nz;
}


function onDocumentMouseMove(event) {
    if (mouseDown) {
        mouseX = (event.clientX - windowHalfX);
        mouseY = (event.clientY - windowHalfY);
        //TODO
    }
}

function inrecaseBoost() {
    boost ++;
}

function decreaseBoost() {
    if (boost > 0 )
        boost --;
}

function stopBoost() {
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

function onWindowResize() {
    windowHalfX = window.innerWidth / 2;
    windowHalfY = window.innerHeight / 2;
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize( window.innerWidth, window.innerHeight );
}

function render() {
    camera.lookAt(earth.position);
    updateShipOrbit();
    updateEarthRotation();
    updateEarthSolRotation();
    renderer.render(scene, camera);
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
    cube.position.set(xpos, ypos, zpos);
    scene.add(ship);
}

function updateShipOrbit() {
    var xpos = posArray[total_seconds][0];
    var ypos = posArray[total_seconds][2];
    var zpos = posArray[total_seconds][1];

    var curMill = (total_seconds + 1) * 1000 - total_milliseconds;
    xpos += curMill / 1000 * speedArray[total_seconds][0];
    ypos += curMill / 1000 * speedArray[total_seconds][1];
    ypos += curMill / 1000 * speedArray[total_seconds][2];
    document.getElementById("pos_x").innerHTML = xpos.toFixed(2);
    document.getElementById("pos_y").innerHTML = ypos.toFixed(2);
    document.getElementById("pos_z").innerHTML = zpos.toFixed(2);

    document.getElementById("speed_x").innerHTML = speedArray[total_seconds][0].toFixed(2);
    document.getElementById("speed_y").innerHTML = speedArray[total_seconds][1].toFixed(2);
    document.getElementById("speed_z").innerHTML = speedArray[total_seconds][2].toFixed(2);

    cube.position.set(xpos, ypos, zpos);
}

function updateEarthRotation() {
    //TODO
    earth.rotation.y -= 0.00000072 * boost;
}

function updateEarthSolRotation() {
    //TODO
    //earth.x -= x * boost;
    //earth.y -= y * boost;
    //earth.z -= z * boost;
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

                //console.log("Pos " + i + " X: " + posArray[i][0] + " Y: " + posArray[i][1] + " Z: " + posArray[i][2]);

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

            //console.log("Pos " + i + " X: " + posArray[i][0] + " Y: " + posArray[i][1] + " Z: " + posArray[i][2]);

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