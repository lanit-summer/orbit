from django.http import HttpResponseRedirect
from django.shortcuts import render_to_response
from django.shortcuts import render
from django.template import Context, loader
from django import forms
import orbit_wrap

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
    maxFlightTime = forms.CharField(required=True, max_length=10)
    numberOfQuants = forms.CharField(required=True, max_length=10)
    quantSizeOfSec = forms.CharField(required=True, max_length=10)
    displayPrecision = forms.CharField(required=True, max_length=10)
    Program = forms.CharField(required=True, widget=forms.Textarea)


def script(request):
    form = MainForm(data=request.POST)
    if request.method == "POST":
        if form.is_valid():
            PositionX = float(form.cleaned_data['PositionX'])
            PositionY = float(form.cleaned_data['PositionY'])
            PositionZ = float(form.cleaned_data['PositionZ'])
            OrientX = float(form.cleaned_data['OrientX'])
            OrientY = float(form.cleaned_data['OrientY'])
            OrientZ = float(form.cleaned_data['OrientZ'])
            shipMass = float(form.cleaned_data['shipMass'])
            fuelMass = float(form.cleaned_data['fuelMass'])
            shipEdgeLength = float(form.cleaned_data['shipEdgeLength'])
            speedFirstX = float(form.cleaned_data['speedFirstX'])
            speedFirstY = float(form.cleaned_data['speedFirstY'])
            speedFirstZ = float(form.cleaned_data['speedFirstZ'])
            maxRotationX = float(form.cleaned_data['maxRotationX'])
            maxRotationY = float(form.cleaned_data['maxRotationY'])
            maxRotationZ = float(form.cleaned_data['maxRotationZ'])
            maxFuelUsagePerSec = float(form.cleaned_data['maxFuelUsagePerSec'])
            impulsePerFuel = float(form.cleaned_data['impulsePerFuel'])
            limitOverload = float(form.cleaned_data['limitOverload'])
            maxTemperature = float(form.cleaned_data['maxTemperature'])
            maxFlightTime = float(form.cleaned_data['maxFlightTime'])
            numberOfQuants = int(form.cleaned_data['numberOfQuants'])
            quantSizeOfSec = float(form.cleaned_data['quantSizeOfSec'])
            displayPrecision = float(form.cleaned_data['displayPrecision'])
            Program = form.cleaned_data['Program']

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

            script = orbit_wrap.generate_celestia_script(flight_plan, quants.quantSizeOfSec)

            with open("getscript/result_script.txt", 'w') as file:
                file.write(script)
            
            return render_to_response('flatpages/script.html', {
                'script': script,
                })
    else:
        form = MainForm()
    return HttpResponseRedirect('/home/')


def get_file(request):

  import os, tempfile, zipfile
  from django.core.servers.basehttp import FileWrapper
  from django.conf import settings
  from django.http import HttpResponse
  import mimetypes

  filename     = "getscript/result_script.txt"
  download_name ="result_script.txt"
  wrapper      = FileWrapper(open(filename))
  content_type = mimetypes.guess_type(filename)[0]
  response     = HttpResponse(wrapper,content_type=content_type)
  response['Content-Length']      = os.path.getsize(filename)    
  response['Content-Disposition'] = "attachment; filename=%s"%download_name
  return response