package orbit.model;

public class ShipPosition {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected ShipPosition(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ShipPosition obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        orbitJNI.delete_ShipPosition(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setPosition(vec value) {
    orbitJNI.ShipPosition_position_set(swigCPtr, this, vec.getCPtr(value), value);
  }

  public vec getPosition() {
    long cPtr = orbitJNI.ShipPosition_position_get(swigCPtr, this);
    return (cPtr == 0) ? null : new vec(cPtr, false);
  }

  public void setOrientation(vec value) {
    orbitJNI.ShipPosition_orientation_set(swigCPtr, this, vec.getCPtr(value), value);
  }

  public vec getOrientation() {
    long cPtr = orbitJNI.ShipPosition_orientation_get(swigCPtr, this);
    return (cPtr == 0) ? null : new vec(cPtr, false);
  }

  public void setSpeedFirst(vec value) {
    orbitJNI.ShipPosition_speedFirst_set(swigCPtr, this, vec.getCPtr(value), value);
  }

  public vec getSpeedFirst() {
    long cPtr = orbitJNI.ShipPosition_speedFirst_get(swigCPtr, this);
    return (cPtr == 0) ? null : new vec(cPtr, false);
  }

  public ShipPosition() {
    this(orbitJNI.new_ShipPosition(), true);
  }

}
