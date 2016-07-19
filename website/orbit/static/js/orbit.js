var container;
var camera, scene, renderer;
var group;
var mouseX = 0, mouseY = 0;
var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;
init();
animate();
function init() {

    container = document.getElementById( 'scene' );
    camera = new THREE.PerspectiveCamera( 60, window.innerWidth / window.innerHeight, 1, 2000 );
    camera.position.z = 500;
    scene = new THREE.Scene();
    group = new THREE.Group();
    scene.add( group );
    // earth
    var loader = new THREE.TextureLoader();
    //FIXME
    var imgurl = "../../static/img/land_ocean_ice_cloud_2048.jpg";
    loader.load(imgurl, function ( texture ) {
                    var geometry = new THREE.SphereGeometry( 200, 30, 30 );
                    var material = new THREE.MeshBasicMaterial( { map: texture, overdraw: 0.5 } );
                    var mesh = new THREE.Mesh( geometry, material );
                    group.add( mesh );
    } );

    var canvas = document.createElement( 'canvas' );
    canvas.width = 128;
    canvas.height = 128;
    var context = canvas.getContext( '2d' );
    var gradient = context.createRadialGradient(
                    canvas.width / 2,
                    canvas.height / 2,
                    0,
                    canvas.width / 2,
                    canvas.height / 2,
                    canvas.width / 2
    );
    gradient.addColorStop( 0.1, 'rgba(210,210,210,1)' );
    gradient.addColorStop( 1, 'rgba(255,255,255,1)' );
    context.fillStyle = gradient;
    context.fillRect( 0, 0, canvas.width, canvas.height );

    renderer = new THREE.CanvasRenderer();
    renderer.setClearColor(0x000000, 1);
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize( window.innerWidth, window.innerHeight - 70);
    container.appendChild( renderer.domElement );
    document.addEventListener( 'mousemove', onDocumentMouseMove, false );
                //
    window.addEventListener( 'resize', onWindowResize, false );
}

function onWindowResize() {
    windowHalfX = window.innerWidth / 2;
    windowHalfY = window.innerHeight / 2;
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize( window.innerWidth, window.innerHeight );
}
function onDocumentMouseMove( event ) {
    //TODO движение камеры только при нажатии левой кнопки например
   //mouseX = ( event.clientX - windowHalfX );
   //mouseY = ( event.clientY - windowHalfY );
}
            //
function animate() {
    requestAnimationFrame( animate );
    render();
}
function render() {
    camera.position.x += ( mouseX - camera.position.x ) * 0.05;
    camera.position.y += ( - mouseY - camera.position.y ) * 0.05;
    camera.lookAt( scene.position );
    group.rotation.y -= 0.001;
    renderer.render( scene, camera );
}