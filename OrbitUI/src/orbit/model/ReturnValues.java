package orbit.model;

public class ReturnValues {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected ReturnValues(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(ReturnValues obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        orbitJNI.delete_ReturnValues(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setPosition(vec value) {
    orbitJNI.ReturnValues_position_set(swigCPtr, this, vec.getCPtr(value), value);
  }

  public vec getPosition() {
    long cPtr = orbitJNI.ReturnValues_position_get(swigCPtr, this);
    return (cPtr == 0) ? null : new vec(cPtr, false);
  }

  public void setSpeed(vec value) {
    orbitJNI.ReturnValues_speed_set(swigCPtr, this, vec.getCPtr(value), value);
  }

  public vec getSpeed() {
    long cPtr = orbitJNI.ReturnValues_speed_get(swigCPtr, this);
    return (cPtr == 0) ? null : new vec(cPtr, false);
  }

  public ReturnValues() {
    this(orbitJNI.new_ReturnValues(), true);
  }

}
