import orbit_wrap

def first_test():
    init_position = orbit_wrap.create_position(100.1, 6001.2, 601.3)
    init_orientation = orbit_wrap.create_orient(0.5, 0.6, 0.7)
    speed_first = orbit_wrap.create_vec(1, 2, 3)

    initial_position = orbit_wrap.create_ship_position(init_position,
                                                       init_orientation,
                                                       speed_first)

    quants = orbit_wrap.create_quants(3, 10)

    ship_edge_length = 1.1
    ship_mass = 2.5
    fuel_mass = 1.3
    max_rotation = orbit_wrap.create_rotation(4.4, 5.5, 6.6)
    max_fuel_usage_per_second = 3.3
    impulse_per_fuel = 2.2
    max_overload = 1
    max_heating = 2

    rot = orbit_wrap.create_rotation(1., 2., 3.)
    parts_of_flight_plan = [orbit_wrap.create_part_of_flight_plan(10, 10, rot) for i in range(3)]

    vector_of_flight_plan = orbit_wrap.orbit.vector_of_part_flight_plan(parts_of_flight_plan)

    ship_params = orbit_wrap.create_ship_params(ship_edge_length,
                                                ship_mass,
                                                fuel_mass,
                                                max_rotation,
                                                max_fuel_usage_per_second,
                                                impulse_per_fuel,
                                                max_overload,
                                                max_heating,
                                                vector_of_flight_plan)

    flight_plan = orbit_wrap.orbit.computeFlightPlan(initial_position, ship_params, quants)

    return orbit_wrap.vector_of_vec_to_str(flight_plan)


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
    print(first_test())
    #------------------------------------------------------

    fl_plan_l = orbit_wrap.parse_input_code('delay   10 \n '
                                            'engine 80 \n torqueX 10 \n torqueY 12 \n torqueZ 3 \n delay 1000 \n'
                                            'engine 10 \n torqueY 70 \n \n    \n  delay 10000 \n'
                                            'torqueZ 50'
    )

    v1 = orbit_wrap.orbit.vector_of_part_flight_plan(fl_plan_l)
    orbit_wrap.vector_flight_plan_print(v1)
