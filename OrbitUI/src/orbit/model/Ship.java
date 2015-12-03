package orbit.model;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.GregorianCalendar;
import java.util.Locale;
import orbit.view.Celestia;

public class Ship {

	private ShipParams params;
	private ShipPosition initial;
	private Quants quants;
	private Celestia celestia;

	public Ship(){
		this.params = new ShipParams();
		this.initial = new ShipPosition();
		this.quants = new Quants();
	}

	public void setParams(double shipEdgeLength,double shipMass,
			double fuelMass,double maxFuelUsagePerSec,
			double impulsePerFuel,double maxOverload,
			double maxHeating){

		this.params = new ShipParams();
		this.params.setFuelMass(fuelMass);
		this.params.setShipEdgeLength(shipEdgeLength);
		this.params.setMaxHeating(maxHeating);
		this.params.setMaxOverload(maxOverload);
		this.params.setShipMass(shipMass);
		this.params.setImpulsePerFuel(impulsePerFuel);
		this.params.setMaxFuelUsagePerSec(maxFuelUsagePerSec);
	}

	public void setInitial(double x,double y,double z){
		vec position =  new vec();
		position.setX(x);
		position.setY(y);
		position.setZ(z);
		initial.setPosition(position);

	}

	public void setFirstSpeed(double x,double y,double z){
		vec firstspeed = new vec();
		firstspeed.setX(x);
		firstspeed.setY(y);
		firstspeed.setZ(z);
		initial.setSpeedFirst(firstspeed);
	}

	public void setOrientation(double x,double y,double z){
		vec orientation = new vec();
		orientation.setX(x);
		orientation.setY(y);
		orientation.setZ(z);
		initial.setOrientation(orientation);
	}

	public void setMaxRotation(double x,double y, double z){
		Rotation maxrot = new Rotation();
		maxrot.setRotationAroundX(x);
		maxrot.setRotationAroundY(y);
		maxrot.setRotationAroundZ(z);
		params.setMaxRotation(maxrot);
	}

	public void setQuants(int quantsize,int quantnumber){
		this.quants.setNumberOfQuants(quantnumber);
		this.quants.setQuantSizeOfSec(quantsize);
	}

	public void setCelestia(Celestia cel){
		this.celestia = cel;
	}

	public void makeTrajectory(){
		vector_of_return_values result = orbit.computeFlightPlan(initial, params, quants);
		createXYZVFile(result);
		runCelestia();
	}

	public void setCommands(String listOfCommands){

		int MAX_FLIGHT_TIME = Integer.MAX_VALUE;
		String [] commands = listOfCommands.split("\n");

		vector_of_part_flight_plan flightPlan =  new vector_of_part_flight_plan();
		PartOfFlightPlan part = createNewPartOfFlightPlan();

		boolean commandsWithoutDelay = true;
		Rotation torque = new Rotation();

		for (String command:commands){
			String [] splitted_commands = command.split(" ");
			if (splitted_commands.length == 2){
				String action = splitted_commands[0];
				String value = splitted_commands[1];
				if (action == "engine"){
					part.setImpulseValue(Double.parseDouble(value));
				}
				else if (action == "torqueX"){
					torque.setRotationAroundX(Double.parseDouble(value));
					part.setRotateValue(torque);
				}
				else if (action == "torqueY"){
					torque.setRotationAroundY(Double.parseDouble(value));
					part.setRotateValue(torque);
				}
				else if (action == "torqueZ"){
					torque.setRotationAroundZ(Double.parseDouble(value));
					part.setRotateValue(torque);
				}
				else if (action == "delay"){
					commandsWithoutDelay = false;
					part.setDelayTime(Integer.parseInt(value));
					flightPlan.add(copyPartOfFlightPlan(part));
				}
			}
		}
		if (commandsWithoutDelay){
			part.setDelayTime(MAX_FLIGHT_TIME);
			flightPlan.add(part);
		}
		this.params.setFlightPlan(flightPlan);
	}

	public PartOfFlightPlan createNewPartOfFlightPlan(){

		PartOfFlightPlan newPlan = new PartOfFlightPlan();
		newPlan.setDelayTime(0);
		newPlan.setImpulseValue(0);

		Rotation rot = new Rotation();
		rot.setRotationAroundX(0);
		rot.setRotationAroundY(0);
		rot.setRotationAroundZ(0);

		newPlan.setRotateValue(rot);
		return newPlan;
	}

	public PartOfFlightPlan copyPartOfFlightPlan(PartOfFlightPlan original){
		PartOfFlightPlan copy = new PartOfFlightPlan();
		copy.setDelayTime(original.getDelayTime());
		copy.setImpulseValue(original.getImpulseValue());
		copy.setRotateValue(original.getRotateValue());
		return copy;
	}

	public Rotation createNewRotation(){
		Rotation newRot = new Rotation();
		newRot.setRotationAroundX(0);
		newRot.setRotationAroundY(0);
		newRot.setRotationAroundZ(0);
		return newRot;
	}

	public void createXYZVFile(vector_of_return_values result) {
		GregorianCalendar calen = new GregorianCalendar(2014, 12, 31, 12, 0, 0);
		PrintWriter writer = null;
		try {
			writer = new PrintWriter(celestia.getPathToTrajectory());
		}catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		for (int i=0;i<quants.getNumberOfQuants();i++){

			double date = julianDate(calen);
			vec speed = result.get(i).getSpeed();
			vec position = result.get(i).getPosition();
			String line = String.format(Locale.US, "%f %f %f %f %f %f %f \n",
					date,position.getX(),position.getY(),position.getZ(),
					speed.getX(),speed.getY(),speed.getZ());
			writer.write(line);
			calen.add(GregorianCalendar.SECOND, (int)quants.getQuantSizeOfSec());
		}
		writer.close();
	}

	private void runCelestia() {
		try {
			Runtime.getRuntime().exec("celestia");
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}

	public double julianDate(GregorianCalendar greg){

		int year = greg.get(GregorianCalendar.YEAR);
		int month = greg.get(GregorianCalendar.MONTH);
		int day = greg.get(GregorianCalendar.DAY_OF_MONTH);
		int hour = greg.get(GregorianCalendar.HOUR_OF_DAY);
		int minute = greg.get(GregorianCalendar.MINUTE);
		int seconds = greg.get(GregorianCalendar.SECOND);

		int a = (14 - month)/12;
		int y = year + 4800 - a;
		int m = month + 12* a -3;
		long jdn = day + (153*m +2)/5 + 365*y + y/4 - y/100 + y/400 - 32045;
		double jd = (hour*3600 + minute*60 + seconds)/86400.0;
		return jdn+jd;
	}

}



