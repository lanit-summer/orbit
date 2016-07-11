var container;
var camera, scene, renderer;
var earth;
var ship;
var mouseX = 0, mouseY = 0;
var boost = 1; //ускорение
var mouseDown = 0;
var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;

var speedArray;
var posArray;

init();
animate();
function init() {

    loadSampleOrbit();
    document.onmousedown = function() {
        ++mouseDown;
    }
    document.onmouseup = function() {
        --mouseDown;
    }

    container = document.getElementById( 'scene' );
    camera = new THREE.PerspectiveCamera( 60, window.innerWidth / window.innerHeight, 1, 1000000);

    scene = new THREE.Scene();
    earth = new THREE.Group();
    scene.add(earth);
    // earth
    var loader = new THREE.TextureLoader();
    //FIXME
    var imgurl = "../../static/img/land_ocean_ice_cloud_2048.jpg";
    loader.load(imgurl, function (texture) { 
                    var geometry = new THREE.SphereGeometry(6371, 30, 30 );
                    var material = new THREE.MeshBasicMaterial({ map: texture, overdraw: 0.5 });
                    var mesh = new THREE.Mesh(geometry, material);
                    earth.add(mesh);
    } );
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
    document.addEventListener('mousemove', onDocumentMouseMove, false );
    document.addEventListener('mousewheel', mousewheel, false );
    document.addEventListener('DOMMouseScroll', mousewheel, false ); // firefox
    window.addEventListener('resize', onWindowResize, false );
}

function onWindowResize() {
    windowHalfX = window.innerWidth / 2;
    windowHalfY = window.innerHeight / 2;
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize( window.innerWidth, window.innerHeight );
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


function animate() {
    requestAnimationFrame(animate);
    render();
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

function updateShipOrbit() {

}

function updateEarthRotation() {
    //TODO
    earth.rotation.y -= 0.001 * boost;
    earth.rotation.x -= 0.001 * boost;
    earth.rotation.z -= 0.001 * boost;
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
    xhr.open("GET","../../static/js/orbit.xyzv");
    xhr.send();
    xhr.onreadystatechange = function(){

        var arr = xhr.responseText.split('\n');
        if (arr.length != 1) {
            posArray = new Array(arr.length);
            speedArray = new Array(arr.length);

            for (var i = 0; i < arr.length; i++) {
                var line = arr[i].split(' ');

                var position = new Array(3);
                position[0] = line[1];
                position[1] = line[2];
                position[2] = line[3];

                posArray[i] = position;

                //console.log("Pos " + i + " X: " + posArray[i][0] + "Y: " + posArray[i][1] + "Z: " + posArray[i][2]);

                speed = new Array(3);
                speed[0] = line[4];
                speed[1] = line[5];
                speed[2] = line[6];

                speedArray[i] = speed;
            }
            boost = Math.ceil(posArray.length / 180);
            console.log(boost);
        }
    };
}