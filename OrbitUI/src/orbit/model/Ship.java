package orbit.model;

import orbit.JOrbit;
import java.awt.Desktop;
import java.io.File;
import java.io.IOException;

public class Ship {

	private double shipEdgeLength;
	private double shipMass;
	private double fuelMass;
	private double maxFuelUsagePerSec;
	private double impulsePerFuel;
	private double maxOverload;
	private double maxHeating;

	private double initialX;
	private double initialY;
	private double initialZ;

	private double orientationX;
	private double orientationY;
	private double orientationZ;

	private double maxRotationX;
	private double maxRotationY;
	private double maxRotationZ;

	private int quantsize;
	private int quantnumber;

	private String commands;

	public Ship(double shipEdgeLength,double shipMass,
			double fuelMass,double maxFuelUsagePerSec,
			double impulsePerFuel,double maxOverload,
			double maxHeating){

		this.shipEdgeLength = shipEdgeLength;
		this.shipMass =  shipMass;
		this.fuelMass =   fuelMass;
		this.maxFuelUsagePerSec = maxFuelUsagePerSec;
		this.impulsePerFuel =  impulsePerFuel;
		this.maxOverload = maxOverload;
		this.maxHeating = maxHeating;
	}

	public void setInitial(double x,double y,double z){
		this.initialX = x;
		this.initialY = y;
		this.initialZ = z;
	}

	public void setOrientation(double x,double y,double z){
		this.orientationX = x;
		this.orientationY = y;
		this.orientationZ = z;
	}

	public void setMaxRotation(double x,double y, double z){
		this.maxRotationX = x;
		this.maxRotationY = y;
		this.maxRotationZ = z;
	}

	public void setCommands(String commands){
		this.commands = commands;
	}

	public void setQuants(int quantsize,int quantnumber){
		this.quantsize = quantsize;
		this.quantnumber = quantnumber;
	}

	public void makeTrajectory(){
		 JOrbit orbit = new JOrbit();
		 orbit.CreateTrajectory(initialX, initialY, initialZ,
							   orientationX, orientationY, orientationZ,
							   shipMass, fuelMass, shipEdgeLength,
							   maxRotationX, maxRotationY, maxRotationZ,
							   maxFuelUsagePerSec,impulsePerFuel, maxOverload,
							   maxHeating, quantsize, quantnumber);
	}

}



