import orbit

# make as param in UI
MAX_FLIGHT_TIME = 320000000  # about 1 year


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


def vector_of_vec_to_str(vector):
    result_string = ''
    for vec in vector:
        result_string += '{vec.x} {vec.y} {vec.z}\n'.format(vec=vec)
    return result_string


Orient = Position = orbit.vec
create_orient = create_position = create_vec


class Part_of_flight_plan:
    def __init__(self, delayTime=0, impulse=0, rotateAroundX=0, rotateAroundY=0, rotateAroundZ=0):
        """
        :param impulse: has type double
        :param rotate: has type Rotation
        """
        self.delayTime = delayTime
        self.impulse = impulse
        self.rotate = create_rotation(rotateAroundX, rotateAroundY, rotateAroundZ)

    def __str__(self):
        return "delayTime = {}, impulse = {}\n" \
               "rotation = {rotation.rotationAroundX}, " \
                          "{rotation.rotationAroundY}, " \
                          "{rotation.rotationAroundZ}" \
               "\n".format(self.delayTime, self.impulse, rotation=self.rotate)
    def __repr__(self):
        return self.__str__()

    def copy(self):
        return Part_of_flight_plan(self.delayTime, self.impulse,
                                   self.rotate.rotationAroundX,
                                   self.rotate.rotationAroundY,
                                   self.rotate.rotationAroundZ)

def parse_input_code(code):
    commands = [command.strip() for command in code.split('\n') if command.strip()]
    flight_plan = []  # list of part_of_flight_plan
    part_of_flight_plan = Part_of_flight_plan()

    # if True then current params are actual to the end of the flight
    there_is_commands_without_delay = False

    for command in commands:
        there_is_commands_without_delay = True
        splited_command = command.split()  # has form [action, value] in correct case
        if len(splited_command) == 2:
            action = splited_command[0]
            splited_command[1] = float(splited_command[1])
            if action == 'engine':
                part_of_flight_plan.impulse = splited_command[1]
            elif action == 'torqueX':
                part_of_flight_plan.rotate.rotationAroundX = splited_command[1]
            elif action == 'torqueY':
                part_of_flight_plan.rotate.rotationAroundY = splited_command[1]
            elif action == 'torqueZ':
                part_of_flight_plan.rotate.rotationAroundZ = splited_command[1]
            elif action == 'delay':
                there_is_commands_without_delay = False
                part_of_flight_plan.delayTime = splited_command[1]
                flight_plan.append(part_of_flight_plan.copy())
            else:
                raise ValueError("Incorrect input set of commands")
        else:
            raise ValueError("Incorrect input set of commands")

    if there_is_commands_without_delay:
        part_of_flight_plan.delayTime = MAX_FLIGHT_TIME
        flight_plan.append(part_of_flight_plan)

    #print(flight_plan)
    return flight_plan