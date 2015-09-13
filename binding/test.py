import orbit_wrap
import datetime

def first_test():
    init_position = orbit_wrap.create_position(0, 0, 6578.1)
    init_orientation = orbit_wrap.create_orient(0, 0, 1)
    speed_first = orbit_wrap.create_vec(0, 0, 0)

    initial_position = orbit_wrap.create_ship_position(init_position,
                                                       init_orientation,
                                                       speed_first)

    quants = orbit_wrap.create_quants(10, 10)

    ship_edge_length = 0.001
    ship_mass = 3
    fuel_mass = 10
    max_rotation = orbit_wrap.create_rotation(10, 10, 10)
    max_fuel_usage_per_second = 100
    impulse_per_fuel = 20
    max_overload = 2
    max_heating = 100

    rot = orbit_wrap.create_rotation(0, 0, 0)
    parts_of_flight_plan = [orbit_wrap.create_part_of_flight_plan(1, 0, rot) for i in range(100000)]

    vector_of_flight_plan = orbit_wrap.orbit.vector_of_part_flight_plan(parts_of_flight_plan)

    fl_plan_l = orbit_wrap.parse_input_code('delay 100000')

    ship_params = orbit_wrap.create_ship_params(ship_edge_length,
                                                ship_mass,
                                                fuel_mass,
                                                max_rotation,
                                                max_fuel_usage_per_second,
                                                impulse_per_fuel,
                                                max_overload,
                                                max_heating,
                                                fl_plan_l)
                                                #vector_of_flight_plan)

    flight_plan = orbit_wrap.orbit.computeFlightPlan(initial_position, ship_params, quants)

    return orbit_wrap.generate_celestia_script(flight_plan, quants.quantSizeOfSec)
    #return orbit_wrap.vector_of_vec_to_str(flight_plan)


if __name__ == '__main__':

    part = orbit_wrap.create_part_of_flight_plan()
    x = []
    x.append(orbit_wrap.copy_part_of_flight_plan(part))
    orbit_wrap.part_of_flight_print(x[0])

    part.delayTime = 100
    part.rotateValue.rotationAroundX = 12

    orbit_wrap.part_of_flight_print(x[0])
    orbit_wrap.part_of_flight_print(part)

    print()
    try:
        print(first_test())
    except:
        print("ok")
    #------------------------------------------------------

    fl_plan_l = orbit_wrap.parse_input_code('delay   10 \n '
                                            'engine 80 \n torqueX 10 \n torqueY 12 \n torqueZ 3 \n delay 1000 \n'
                                            'engine 10 \n torqueY 70 \n \n    \n  delay 10000 \n'
                                            'torqueZ 50'
    )


    v1 = orbit_wrap.orbit.vector_of_part_flight_plan(fl_plan_l)
    orbit_wrap.vector_flight_plan_print(v1)

    dt = datetime.datetime(2015, 1, 1)
    print(dt + datetime.timedelta(seconds=100))
