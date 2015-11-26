package orbit.model;

public class ShipParams {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected ShipParams(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ShipParams obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        orbitJNI.delete_ShipParams(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setShipEdgeLength(double value) {
    orbitJNI.ShipParams_shipEdgeLength_set(swigCPtr, this, value);
  }

  public double getShipEdgeLength() {
    return orbitJNI.ShipParams_shipEdgeLength_get(swigCPtr, this);
  }

  public void setShipMass(double value) {
    orbitJNI.ShipParams_shipMass_set(swigCPtr, this, value);
  }

  public double getShipMass() {
    return orbitJNI.ShipParams_shipMass_get(swigCPtr, this);
  }

  public void setFuelMass(double value) {
    orbitJNI.ShipParams_fuelMass_set(swigCPtr, this, value);
  }

  public double getFuelMass() {
    return orbitJNI.ShipParams_fuelMass_get(swigCPtr, this);
  }

  public void setMaxRotation(Rotation value) {
    orbitJNI.ShipParams_maxRotation_set(swigCPtr, this, Rotation.getCPtr(value), value);
  }

  public Rotation getMaxRotation() {
    long cPtr = orbitJNI.ShipParams_maxRotation_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Rotation(cPtr, false);
  }

  public void setMaxFuelUsagePerSec(double value) {
    orbitJNI.ShipParams_maxFuelUsagePerSec_set(swigCPtr, this, value);
  }

  public double getMaxFuelUsagePerSec() {
    return orbitJNI.ShipParams_maxFuelUsagePerSec_get(swigCPtr, this);
  }

  public void setImpulsePerFuel(double value) {
    orbitJNI.ShipParams_impulsePerFuel_set(swigCPtr, this, value);
  }

  public double getImpulsePerFuel() {
    return orbitJNI.ShipParams_impulsePerFuel_get(swigCPtr, this);
  }

  public void setFlightPlan(vector_of_part_flight_plan value) {
    orbitJNI.ShipParams_flightPlan_set(swigCPtr, this, vector_of_part_flight_plan.getCPtr(value), value);
  }

  public vector_of_part_flight_plan getFlightPlan() {
    long cPtr = orbitJNI.ShipParams_flightPlan_get(swigCPtr, this);
    return (cPtr == 0) ? null : new vector_of_part_flight_plan(cPtr, false);
  }

  public void setMaxOverload(double value) {
    orbitJNI.ShipParams_maxOverload_set(swigCPtr, this, value);
  }

  public double getMaxOverload() {
    return orbitJNI.ShipParams_maxOverload_get(swigCPtr, this);
  }

  public void setMaxHeating(double value) {
    orbitJNI.ShipParams_maxHeating_set(swigCPtr, this, value);
  }

  public double getMaxHeating() {
    return orbitJNI.ShipParams_maxHeating_get(swigCPtr, this);
  }

  public ShipParams() {
    this(orbitJNI.new_ShipParams(), true);
  }

}
