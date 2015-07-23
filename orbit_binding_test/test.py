import orbit_wrap

def first_test():
    init_position = orbit_wrap.create_position(1.1, 1.2, 1.3)
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
    impulse_flight_plan = [0.5 ** i for i in range(3)]
    rotate_flight_plan = [orbit_wrap.create_rotation(0.1, 0.2, 0.3) for i in range(3)]

    ship_params = orbit_wrap.create_ship_params(ship_edge_length,
                                                ship_mass,
                                                fuel_mass,
                                                max_rotation,
                                                max_fuel_usage_per_second,
                                                impulse_per_fuel,
                                                impulse_flight_plan,
                                                rotate_flight_plan)

    flight_plan = orbit_wrap.orbit.computeFlightPlan(initial_position, ship_params, quants)

    return orbit_wrap.vector_of_vec_to_str(flight_plan)


def second_test():

    """
    ShipPosition initialPosition;
     initialPosition.position = {0.0, 0.0, 6478.0};
     initialPosition.orientation = {1.0, 0.0, 0.0};
     initialPosition.speedFirst = {8.0, 0.0, 0.0};
     ShipParams shipParams;
     Quants quants;
     shipParams.shipEdgeLength = 0.001;
     shipParams.shipMass = 10.0;
     shipParams.fuelMass = 0.0;
     shipParams.maxRotation = {10.0, 10.0, 10.0};
     shipParams.maxFuelUsagePerSec = 100.0;
     shipParams.impulsePerFuel = 20.0;
     quants.quantSizeOfSec = 1.0;
     quants.numberOfQuants = 3.0;
     shipParams.impulseFlightPlan = {0.0, 0.0, 0.0};
     shipParams.rotateFlightPlan = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
     vector<Position> res = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
     vector<Position> result = computeFlightPlan(initialPosition, shipParams, quants);

    """

    init_position = orbit_wrap.create_position(0.0, 0.0, 6478.0)
    init_orientation = orbit_wrap.create_orient(1.0, 0.0, 0.0)
    speed_first = orbit_wrap.create_vec(8.0, 0.0, 0.0)

    initial_position = orbit_wrap.create_ship_position(init_position,
                                                       init_orientation,
                                                       speed_first)

    quants = orbit_wrap.create_quants(10, 1)

    ship_edge_length = 0.001
    ship_mass = 10
    fuel_mass = 0
    max_rotation = orbit_wrap.create_rotation(10, 10, 10)
    max_fuel_usage_per_second = 100
    impulse_per_fuel = 20
    impulse_flight_plan = [0.0 for i in range(10)]
    rotate_flight_plan = [orbit_wrap.create_rotation(0, 0, 0) for i in range(10)]

    ship_params = orbit_wrap.create_ship_params(ship_edge_length,
                                                ship_mass,
                                                fuel_mass,
                                                max_rotation,
                                                max_fuel_usage_per_second,
                                                impulse_per_fuel,
                                                impulse_flight_plan,
                                                rotate_flight_plan)

    flight_plan = orbit_wrap.orbit.computeFlightPlan(initial_position, ship_params, quants)

    return orbit_wrap.vector_of_vec_to_str(flight_plan)


if __name__ == '__main__':
    v = orbit_wrap.orbit.vector_of_double([0.5 ** i for i in range(10)])
    orbit_wrap.primitive_vector_print(v)

    p1 = orbit_wrap.create_position(1.1, 2.2, 3.3)
    p2 = orbit_wrap.create_position(1.4, 2.4, 3.4)
    p3 = orbit_wrap.create_position(1.5, 2.5, 3.5)

    vp = orbit_wrap.orbit.vector_of_position([p1, p2, p3])
    orbit_wrap.vector_of_vec_print(vp)

    r1 = orbit_wrap.create_rotation(1.1, 2.2, 3.3)
    r2 = orbit_wrap.create_rotation(1.4, 2.4, 3.4)
    r3 = orbit_wrap.create_rotation(1.5, 2.5, 3.5)

    vr = orbit_wrap.orbit.vector_of_rotation([r1, r2, r3])
    print()
    orbit_wrap.vector_of_vec_print(vr)

    s = orbit_wrap.vector_of_vec_to_str(vp)
    print()
    print(s)

    #------------------------------------------------------
    print()
    print(first_test())
    print()
    print(second_test())

    orbit_wrap.parse_input_code('delay   10 \n '
                                'engine 80 \n torqueX 10 \n torqueY 12 \n torqueZ 3 \n delay 1000 \n'
                                'engine 10 \n torqueY 70 \n \n    \n  delay 10000 \n'
                                'torqueY 50'
    )

    part = orbit_wrap.Part_of_flight_plan(1, 2, 3, 4, 5)
    x = []
    x.append(part.copy())
    print(x[0])
    part.delayTime = 2000
    print(x[0])
    print(part)