package orbit.model;

public class vec {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected vec(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(vec obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        orbitJNI.delete_vec(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setX(double value) {
    orbitJNI.vec_x_set(swigCPtr, this, value);
  }

  public double getX() {
    return orbitJNI.vec_x_get(swigCPtr, this);
  }

  public void setY(double value) {
    orbitJNI.vec_y_set(swigCPtr, this, value);
  }

  public double getY() {
    return orbitJNI.vec_y_get(swigCPtr, this);
  }

  public void setZ(double value) {
    orbitJNI.vec_z_set(swigCPtr, this, value);
  }

  public double getZ() {
    return orbitJNI.vec_z_get(swigCPtr, this);
  }

  public vec() {
    this(orbitJNI.new_vec(), true);
  }

}
