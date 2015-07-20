import orbit


def create_vec(coordX, coordY, coordZ):
    vec = orbit.vec()
    vec.x = coordX
    vec.y = coordY
    vec.z = coordZ
    return vec


def create_rotation(aroundX, aroundY, aroundZ):
    rotation = orbit.Rotation()
    rotation.rotationAroundX = aroundX
    rotation.rotationAroundY = aroundY
    rotation.rotationAroundZ = aroundZ
    return rotation


def create_ship_params(ship_edge_length,
                       ship_mass,
                       fuel_mass,
                       max_rotation,
                       max_fuel_usage_per_second,
                       impulse_per_fuel,
                       impulse_flight_plan,
                       rotate_flight_plan) :
    """
    :param ship_edge_length: has type double
    :param ship_mass: has type double
    :param fuel_mass: has type double
    :param max_rotation: has type rotation
    :param max_fuel_usage_per_second: has type double
    :param impulse_per_fuel: has type double
    :param impulse_flight_plan: has type list of doubles
    :param rotate_flight_plan: has type list of rotations
    :return: object that ha type ShipParams
    """
    ship_params = orbit.ShipParams()
    ship_params.shipEdgeLength = ship_edge_length
    ship_params.shipMass = ship_mass
    ship_params.fuelMass = fuel_mass
    ship_params.maxRotation = max_rotation
    ship_params.maxFuelUsagePerSec = max_fuel_usage_per_second
    ship_params.impulsePerFuel = impulse_per_fuel
    ship_params.impulseFlightPlan = orbit.vector_of_double(impulse_flight_plan)
    ship_params.rotateFlightPlan = orbit.vector_of_rotation(rotate_flight_plan)

    return ship_params


def create_ship_position(position, orientation, speed_first):
    """
    :param position: has type Position or vec
    :param orientation: has type Orient or vec
    :param first_speed: ahs type vec
    :return:
    """
    ship_position = orbit.ShipPosition()
    ship_position.position = position
    ship_position.orientation = orientation
    ship_position.speedFirst = speed_first

    return ship_position


def create_quants(number_of_quants, quant_size_of_sec):
    quants = orbit.Quants()
    quants.numberOfQuants = number_of_quants
    quants.quantSizeOfSec = quant_size_of_sec

    return quants


def vec_print(vector):
    print(vector.x, vector.y, vector.z)


def rotation_print(vector):
    print(vector.rotationAroundX,
          vector.rotationAroundY,
          vector.rotationAroundZ)


def primitive_vector_print(vector):
    for item in vector:
        print(item, end=' ')
    print()


def vector_of_vec_print(vector):
    if vector:
        if 'x' in dir(vector[0]):
            for item in vector:
                vec_print(item)
        else:
            for item in vector:
                rotation_print(item)


Orient = Position = orbit.vec
create_orient = create_position = create_vec


def first_test():
    init_position = create_position(1.1, 1.2, 1.3)
    init_orientation = create_orient(0.5, 0.6, 0.7)
    speed_first = create_vec(1, 2, 3)

    initial_position = create_ship_position( init_position,
                                             init_orientation,
                                             speed_first)

    quants = create_quants(3, 10)

    ship_edge_length = 1.1
    ship_mass = 2.5
    fuel_mass = 1.3
    max_rotation = create_rotation(4.4, 5.5, 6.6)
    max_fuel_usage_per_second = 3.3
    impulse_per_fuel = 2.2
    impulse_flight_plan = [0.5 ** i for i in range(3)]
    rotate_flight_plan = [create_rotation(0.1, 0.2, 0.3) for i in range(3)]

    ship_params = create_ship_params(ship_edge_length,
                                    ship_mass,
                                    fuel_mass,
                                    max_rotation,
                                    max_fuel_usage_per_second,
                                    impulse_per_fuel,
                                    impulse_flight_plan,
                                    rotate_flight_plan)

    flight_plan = orbit.computeFlightPlan(initial_position, ship_params, quants)

    vector_of_vec_print(flight_plan)


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

    init_position = create_position(0.0, 0.0, 6478.0)
    init_orientation = create_orient(1.0, 0.0, 0.0)
    speed_first = create_vec(8.0, 0.0, 0.0)

    initial_position = create_ship_position( init_position,
                                             init_orientation,
                                             speed_first)

    quants = create_quants(10, 1)

    ship_edge_length = 0.001
    ship_mass = 10
    fuel_mass = 0
    max_rotation = create_rotation(10, 10, 10)
    max_fuel_usage_per_second = 100
    impulse_per_fuel = 20
    impulse_flight_plan = [0.0 for i in range(10)]
    rotate_flight_plan = [create_rotation(0, 0, 0) for i in range(10)]

    ship_params = create_ship_params(ship_edge_length,
                                    ship_mass,
                                    fuel_mass,
                                    max_rotation,
                                    max_fuel_usage_per_second,
                                    impulse_per_fuel,
                                    impulse_flight_plan,
                                    rotate_flight_plan)

    flight_plan = orbit.computeFlightPlan(initial_position, ship_params, quants)

    vector_of_vec_print(flight_plan)


if __name__ == '__main__':
    v = orbit.vector_of_double([0.5 ** i for i in range(10)])
    primitive_vector_print(v)

    p1 = create_position(1.1, 2.2, 3.3)
    p2 = create_position(1.4, 2.4, 3.4)
    p3 = create_position(1.5, 2.5, 3.5)

    vp = orbit.vector_of_position([p1, p2, p3])
    vector_of_vec_print(vp)

    r1 = create_rotation(1.1, 2.2, 3.3)
    r2 = create_rotation(1.4, 2.4, 3.4)
    r3 = create_rotation(1.5, 2.5, 3.5)

    vr = orbit.vector_of_rotation([r1, r2, r3])
    vector_of_vec_print(vr)

    #------------------------------------------------------
    print()
    first_test()
    print()
    second_test()