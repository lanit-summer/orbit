import datetime
import orbitswig

# make as param in UI
MAX_FLIGHT_TIME = 320000000  # about 1 year


def create_vec(coordX, coordY, coordZ):
    vec = orbitswig.vec()
    vec.x = coordX
    vec.y = coordY
    vec.z = coordZ
    return vec


def create_rotation(aroundX, aroundY, aroundZ):
    rotation = orbitswig.Rotation()
    rotation.rotationAroundX = aroundX
    rotation.rotationAroundY = aroundY
    rotation.rotationAroundZ = aroundZ
    return rotation


def create_part_of_flight_plan(delay_time=0, impulse_value=0, rotation_value=create_rotation(0, 0, 0)):
    """
    :param delay_time: has type int
    :param impulse_value:  has type double
    :param rotation_value: has type Rotation
    :return: object PartOfFlightPlan
    """
    part_of_flight_plan = orbitswig.PartOfFlightPlan()
    part_of_flight_plan.delayTime = delay_time
    part_of_flight_plan.impulseValue = impulse_value
    part_of_flight_plan.rotateValue = rotation_value

    return part_of_flight_plan


def create_ship_params(ship_edge_length,
                       ship_mass,
                       fuel_mass,
                       max_rotation,
                       max_fuel_usage_per_second,
                       impulse_per_fuel,
                       max_overload,
                       max_heating,
                       flight_plan):
    """
    :param ship_edge_length: has type double
    :param ship_mass: has type double
    :param fuel_mass: has type double
    :param max_rotation: has type rotation
    :param max_fuel_usage_per_second: has type double
    :param impulse_per_fuel: has type double
    :param max_overload: has type double
    :param max_heating: has type double
    :param flight_plan has type list of Part_of_flight_plan
    :return: object that ha type ShipParams
    """
    ship_params = orbitswig.ShipParams()
    ship_params.shipEdgeLength = ship_edge_length
    ship_params.shipMass = ship_mass
    ship_params.fuelMass = fuel_mass
    ship_params.maxRotation = max_rotation
    ship_params.maxFuelUsagePerSec = max_fuel_usage_per_second
    ship_params.impulsePerFuel = impulse_per_fuel
    ship_params.maxOverload = max_overload
    ship_params.maxHeating = max_heating
    ship_params.flightPlan = orbitswig.vector_of_part_flight_plan(flight_plan)

    return ship_params


def create_ship_position(position, orientation, speed_first):
    """
    :param position: has type Position or vec
    :param orientation: has type Orient or vec
    :param first_speed: ahs type vec
    :return:
    """
    ship_position = orbitswig.ShipPosition()
    ship_position.position = position
    ship_position.orientation = orientation
    ship_position.speedFirst = speed_first

    return ship_position


def create_quants(number_of_quants, quant_size_of_sec):
    quants = orbitswig.Quants()
    quants.numberOfQuants = number_of_quants
    quants.quantSizeOfSec = quant_size_of_sec

    return quants


def copy_rotation(rotation):
    return create_rotation(rotation.rotationAroundX,
                           rotation.rotationAroundY,
                           rotation.rotationAroundZ)


def copy_part_of_flight_plan(part_of_fligth_plan):
    return create_part_of_flight_plan(part_of_fligth_plan.delayTime,
                                      part_of_fligth_plan.impulseValue,
                                      copy_rotation(part_of_fligth_plan.rotateValue))


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
            # for vec
            for item in vector:
                vec_print(item)
        else:
            # for rotation
            for item in vector:
                rotation_print(item)


def part_of_flight_print(part_of_flight_plan):
    print(part_of_flight_plan.delayTime)
    print(part_of_flight_plan.impulseValue)
    rotation_print(part_of_flight_plan.rotateValue)


def vector_flight_plan_print(vector):
    for part_flight_plan in vector:
        part_of_flight_print(part_flight_plan)
        print()


def vec_to_str(vec):
    return '{vec.x} {vec.y} {vec.z}'.format(vec=vec)


def return_value_to_str(return_value):
    return vec_to_str(return_value.position) + ' ' + vec_to_str(return_value.speed)


Orient = Position = orbitswig.vec
create_orient = create_position = create_vec


def parse_input_code(code):
    if not code:
        raise ValueError('List of command is empty')
    commands = [command.strip() for command in code.split('\n') if command.strip()]
    flight_plan = []  # list of part_of_flight_plan
    part_of_flight_plan = create_part_of_flight_plan()  # Part_of_flight_plan()

    # if True then current params are actual to the end of the flight
    there_is_commands_without_delay = False

    for command in commands:
        there_is_commands_without_delay = True
        splited_command = command.split()  # has form [action, value] in correct case
        if len(splited_command) == 2:
            action = splited_command[0]
            if action == 'engine':
                part_of_flight_plan.impulseValue = float(splited_command[1])
            elif action == 'torqueX':
                part_of_flight_plan.rotateValue.rotationAroundX = float(splited_command[1])
            elif action == 'torqueY':
                part_of_flight_plan.rotateValue.rotationAroundY = float(splited_command[1])
            elif action == 'torqueZ':
                part_of_flight_plan.rotateValue.rotationAroundZ = float(splited_command[1])
            elif action == 'delay':
                there_is_commands_without_delay = False
                part_of_flight_plan.delayTime = int(splited_command[1])
                flight_plan.append(copy_part_of_flight_plan(part_of_flight_plan))
            else:
                raise ValueError("Incorrect input set of commands")
        else:
            raise ValueError("Incorrect input set of commands")

    if there_is_commands_without_delay:
        part_of_flight_plan.delayTime = MAX_FLIGHT_TIME
        flight_plan.append(part_of_flight_plan)

    #print(flight_plan)
    return flight_plan


def julian_day(year, month=1, day=1):
        """Given a proleptic Gregorian calendar date, return a Julian day int."""
        janfeb = month < 3
        return (day
                + 1461 * (year + 4800 - janfeb) // 4
                + 367 * (month - 2 + janfeb * 12) // 12
                - 3 * ((year + 4900 - janfeb) // 100) // 4
                - 32075)


DAY_S = 86400.0

def julian_date(year, month=1, day=1, hour=0, minute=0, second=0.0):
    """Given a proleptic Gregorian calendar date, return a Julian date float."""
    jd = julian_day(year, month, day) - 0.5 + (
        second + minute * 60.0 + hour * 3600.0) / DAY_S
    return round(jd, 5)


def generate_celestia_script(vector_of_ret_val, quant_size):
    """
    :param vector_of_ret_val: vector of ReturnTypes
    :param quant_size: number sec in quant
    :return: object str with script for celestia
    """

    current_dt = datetime.datetime(2015, 1, 1)
    delta = datetime.timedelta(seconds=quant_size)

    script = ''
    for ret_value in vector_of_ret_val:
        script += '{datetime} {value}\n'.format(datetime=julian_date(current_dt.year,
                                                                     current_dt.month,
                                                                     current_dt.day,
                                                                     current_dt.hour,
                                                                     current_dt.minute,
                                                                     current_dt.second),
                                                value=return_value_to_str(ret_value)
        )
        current_dt += delta

    return script
