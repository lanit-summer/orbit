package orbit.model;

public class Rotation {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected Rotation(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Rotation obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        orbitJNI.delete_Rotation(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setRotationAroundX(double value) {
    orbitJNI.Rotation_rotationAroundX_set(swigCPtr, this, value);
  }

  public double getRotationAroundX() {
    return orbitJNI.Rotation_rotationAroundX_get(swigCPtr, this);
  }

  public void setRotationAroundY(double value) {
    orbitJNI.Rotation_rotationAroundY_set(swigCPtr, this, value);
  }

  public double getRotationAroundY() {
    return orbitJNI.Rotation_rotationAroundY_get(swigCPtr, this);
  }

  public void setRotationAroundZ(double value) {
    orbitJNI.Rotation_rotationAroundZ_set(swigCPtr, this, value);
  }

  public double getRotationAroundZ() {
    return orbitJNI.Rotation_rotationAroundZ_get(swigCPtr, this);
  }

  public Rotation() {
    this(orbitJNI.new_Rotation(), true);
  }

}
