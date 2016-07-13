
# -*- coding: utf-8 -*-
from __future__ import with_statement
from django.http import HttpResponseRedirect
from django.shortcuts import render_to_response
from django.shortcuts import render
from django.template import Context, loader
from django import forms
import orbit_wrap

global script

class MainForm(forms.Form):
    PositionX = forms.CharField(required=True, max_length=10)
    PositionY = forms.CharField(required=True, max_length=10)
    PositionZ = forms.CharField(required=True, max_length=10)
    OrientX = forms.CharField(required=True, max_length=10)
    OrientY = forms.CharField(required=True, max_length=10)
    OrientZ = forms.CharField(required=True, max_length=10)
    shipMass = forms.CharField(required=True, max_length=10)
    fuelMass = forms.CharField(required=True, max_length=10)
    shipEdgeLength = forms.CharField(required=True, max_length=10)
    speedFirstX = forms.CharField(required=True, max_length=10)
    speedFirstY = forms.CharField(required=True, max_length=10)
    speedFirstZ = forms.CharField(required=True, max_length=10)
    maxRotationX = forms.CharField(required=True, max_length=10)
    maxRotationY = forms.CharField(required=True, max_length=10)
    maxRotationZ = forms.CharField(required=True, max_length=10)
    maxFuelUsagePerSec = forms.CharField(required=True, max_length=10)
    impulsePerFuel = forms.CharField(required=True, max_length=10)
    limitOverload = forms.CharField(required=True, max_length=10)
    maxTemperature = forms.CharField(required=True, max_length=10)
    maxFlightTime = forms.CharField(required=False, max_length=10)
    numberOfQuants = forms.CharField(required=True, max_length=10)
    quantSizeOfSec = forms.CharField(required=True, max_length=10)
    displayPrecision = forms.CharField(required=True, max_length=10)
    Program = forms.CharField(required=False, widget=forms.Textarea)

def calculator(request):
    form = MainForm(data=request.POST)
    form.data['PositionX'] = request.session.get('PositionX')
    form.data['PositionX'] = request.session.get('PositionX')
    form.data['PositionY'] = request.session.get('PositionY')
    form.data['PositionZ'] = request.session.get('PositionZ')
    form.data['OrientX'] = request.session.get('OrientX')
    form.data['OrientY'] = request.session.get('OrientY')
    form.data['OrientZ'] = request.session.get('OrientZ')
    form.data['shipMass'] = request.session.get('shipMass')
    form.data['fuelMass'] = request.session.get('fuelMass')
    form.data['shipEdgeLength'] = request.session.get('shipEdgeLength')
    form.data['speedFirstX'] = request.session.get('speedFirstX')
    form.data['speedFirstY'] = request.session.get('speedFirstY')
    form.data['speedFirstZ'] = request.session.get('speedFirstZ')
    form.data['maxRotationX'] = request.session.get('maxRotationX')
    form.data['maxRotationY'] = request.session.get('maxRotationY')
    form.data['maxRotationZ'] = request.session.get('maxRotationZ')
    form.data['maxFuelUsagePerSec'] = request.session.get('maxFuelUsagePerSec')
    form.data['impulsePerFuel'] = request.session.get('impulsePerFuel')
    form.data['limitOverload'] = request.session.get('limitOverload')
    form.data['maxTemperature'] = request.session.get('maxTemperature')
    form.data['maxFlightTime'] = request.session.get('maxFlightTime')
    form.data['numberOfQuants'] = request.session.get('numberOfQuants')
    form.data['quantSizeOfSec'] = request.session.get('quantSizeOfSec')
    form.data['displayPrecision'] = request.session.get('displayPrecision')
    form.data['Program'] = request.session.get('Program')   
    return render(request, 'flatpages/calculator.html', {'form': form})
    
def script(request):
    form = MainForm(data=request.POST)
    if request.method == "POST" and form.is_valid():
        PositionX = float(form.cleaned_data['PositionX']); request.session['PositionX'] = form.data['PositionX']
        PositionY = float(form.cleaned_data['PositionY']); request.session['PositionY'] = form.data['PositionY']
        PositionZ = float(form.cleaned_data['PositionZ']); request.session['PositionZ'] = form.data['PositionZ']
        OrientX = float(form.cleaned_data['OrientX']); request.session['OrientX'] = form.data['OrientX']
        OrientY = float(form.cleaned_data['OrientY']); request.session['OrientY'] = form.data['OrientY']
        OrientZ = float(form.cleaned_data['OrientZ']); request.session['OrientZ'] = form.data['OrientZ']
        shipMass = float(form.cleaned_data['shipMass']); request.session['shipMass'] = form.data['shipMass']
        fuelMass = float(form.cleaned_data['fuelMass']); request.session['fuelMass'] = form.data['fuelMass']
        shipEdgeLength = float(form.cleaned_data['shipEdgeLength']); request.session['shipEdgeLength'] = form.data['shipEdgeLength']
        speedFirstX = float(form.cleaned_data['speedFirstX']); request.session['speedFirstX'] = form.data['speedFirstX']
        speedFirstY = float(form.cleaned_data['speedFirstY']); request.session['speedFirstY'] = form.data['speedFirstY']
        speedFirstZ = float(form.cleaned_data['speedFirstZ']); request.session['speedFirstZ'] = form.data['speedFirstZ']
        maxRotationX = float(form.cleaned_data['maxRotationX']); request.session['maxRotationX'] = form.data['maxRotationX']
        maxRotationY = float(form.cleaned_data['maxRotationY']); request.session['maxRotationY'] = form.data['maxRotationY']
        maxRotationZ = float(form.cleaned_data['maxRotationZ']); request.session['maxRotationZ'] = form.data['maxRotationZ']
        maxFuelUsagePerSec = float(form.cleaned_data['maxFuelUsagePerSec']); request.session['maxFuelUsagePerSec'] = form.data['maxFuelUsagePerSec']
        impulsePerFuel = float(form.cleaned_data['impulsePerFuel']); request.session['impulsePerFuel'] = form.data['impulsePerFuel']
        limitOverload = float(form.cleaned_data['limitOverload']); request.session['limitOverload'] = form.data['limitOverload']
        maxTemperature = float(form.cleaned_data['maxTemperature']); request.session['maxTemperature'] = form.data['maxTemperature']
       # maxFlightTime = float(form.cleaned_data['maxFlightTime']); request.session['maxFlightTime'] = form.data['maxFlightTime']
        numberOfQuants = int(form.cleaned_data['numberOfQuants']); request.session['numberOfQuants'] = form.data['numberOfQuants']
        quantSizeOfSec = float(form.cleaned_data['quantSizeOfSec']); request.session['quantSizeOfSec'] = form.data['quantSizeOfSec']
        displayPrecision = float(form.cleaned_data['displayPrecision']); request.session['displayPrecision'] = form.data['displayPrecision']
        Program = form.cleaned_data['Program']; request.session['Program'] = form.data['Program']

        init_position = orbit_wrap.create_position(PositionX, PositionY, PositionZ)
        init_orientation = orbit_wrap.create_orient(OrientX, OrientY, OrientZ)
        speed_first = orbit_wrap.create_vec(speedFirstX, speedFirstY, speedFirstZ)

        initial_position = orbit_wrap.create_ship_position( init_position,
                                                 init_orientation,
                                                 speed_first)

        quants = orbit_wrap.create_quants(numberOfQuants, quantSizeOfSec)

        ship_edge_length = shipEdgeLength
        ship_mass = shipMass
        fuel_mass = fuelMass
        max_rotation = orbit_wrap.create_rotation(maxRotationX, maxRotationY, maxRotationZ)
        max_fuel_usage_per_second = maxFuelUsagePerSec
        impulse_per_fuel = impulsePerFuel
        max_overload = limitOverload
        max_heating = maxTemperature


        rot = orbit_wrap.create_rotation(0, 0, 0)
        parts_of_flight_plan = [orbit_wrap.create_part_of_flight_plan(1, 0, rot) for i in range(100000)]

        vector_of_flight_plan = orbit_wrap.orbitswig.vector_of_part_flight_plan(parts_of_flight_plan)

        fl_plan_l = orbit_wrap.parse_input_code(Program)

        ship_params = orbit_wrap.create_ship_params(ship_edge_length,
                                            ship_mass,
                                            fuel_mass,
                                            max_rotation,
                                            max_fuel_usage_per_second,
                                            impulse_per_fuel,
                                            max_overload,
                                            max_heating,
                                            fl_plan_l)

        flight_plan = orbit_wrap.orbitswig.computeFlightPlan(initial_position, ship_params, quants)
        global script
        script = orbit_wrap.generate_celestia_script(flight_plan, quants.quantSizeOfSec)

        return render(request, 'flatpages/script.html', {'form': form, 'script': script})
    else:
        form = MainForm(data=request.POST)
        form_error = "Заполнены не все поля формы."    
    return render(request, 'flatpages/calculator.html', {'form': form, 'form_error': form_error})

def clear_form(request):
    try:
        del request.session['PositionX']
        del request.session['PositionY']
        del request.session['PositionZ']
        del request.session['OrientX']
        del request.session['OrientY']
        del request.session['OrientZ']
        del request.session['shipMass']
        del request.session['fuelMass']
        del request.session['shipEdgeLength']
        del request.session['speedFirstX']
        del request.session['speedFirstY']
        del request.session['speedFirstZ']
        del request.session['maxRotationX']
        del request.session['maxRotationY']
        del request.session['maxRotationZ']
        del request.session['maxFuelUsagePerSec']
        del request.session['impulsePerFuel']
        del request.session['limitOverload']
        del request.session['maxTemperature']
       # del request.session['maxFlightTime']
        del request.session['numberOfQuants']
        del request.session['quantSizeOfSec']
        del request.session['displayPrecision']
        del request.session['Program'] 
    except KeyError:
        pass
    return HttpResponseRedirect('/calculator/')

def visualization(request):
    global script
    return render(request, 'flatpages/visualization.html', {'script':script})

def zipdir(basedir, archivename):
    from contextlib import closing
    from zipfile import ZipFile, ZIP_DEFLATED
    import os   
    assert os.path.isdir(basedir)
    with closing(ZipFile(archivename, "w", ZIP_DEFLATED)) as z:
	z.write("getscript/Orbit-test/data/orbit.xyzv", "data/orbit.xyzv")
	z.write("getscript/Orbit-test/models/orbit.3ds", "models/orbit.3ds")
	z.write("getscript/Orbit-test/orbit.ssc", "orbit.ssc")
        z.write("getscript/spacesimulator.cel", "spacesimulator.cel")
	z.write("getscript/install.txt", "install.txt")
def get_file(request):
    import os, tempfile, zipfile
    from wsgiref.util import FileWrapper
    from django.conf import settings
    from django.http import HttpResponse
    import mimetypes
    from zipfile import ZipFile   
    with open("getscript/Orbit-test/data/orbit.xyzv", 'w') as file:
        file.write(script)     
    zipdir("getscript/Orbit-test", "getscript/SimulatorTrajectory.zip")
    filename     = "getscript/SimulatorTrajectory.zip"
    download_name = "SimulatorTrajectory.zip"
    wrapper      = FileWrapper(open(filename))
    content_type = mimetypes.guess_type(filename)[0]
    response     = HttpResponse(wrapper,content_type=content_type)
    response['Content-Length'] = os.path.getsize(filename)    
    response['Content-Disposition'] = "attachment; filename=%s"%download_name
    return response
