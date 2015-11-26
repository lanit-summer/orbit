package orbit.model;

public class PartOfFlightPlan {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected PartOfFlightPlan(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PartOfFlightPlan obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        orbitJNI.delete_PartOfFlightPlan(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setDelayTime(int value) {
    orbitJNI.PartOfFlightPlan_delayTime_set(swigCPtr, this, value);
  }

  public int getDelayTime() {
    return orbitJNI.PartOfFlightPlan_delayTime_get(swigCPtr, this);
  }

  public void setImpulseValue(double value) {
    orbitJNI.PartOfFlightPlan_impulseValue_set(swigCPtr, this, value);
  }

  public double getImpulseValue() {
    return orbitJNI.PartOfFlightPlan_impulseValue_get(swigCPtr, this);
  }

  public void setRotateValue(Rotation value) {
    orbitJNI.PartOfFlightPlan_rotateValue_set(swigCPtr, this, Rotation.getCPtr(value), value);
  }

  public Rotation getRotateValue() {
    long cPtr = orbitJNI.PartOfFlightPlan_rotateValue_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Rotation(cPtr, false);
  }

  public PartOfFlightPlan() {
    this(orbitJNI.new_PartOfFlightPlan(), true);
  }

}
