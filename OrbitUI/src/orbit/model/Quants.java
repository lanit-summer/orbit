package orbit.model;

public class Quants {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected Quants(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Quants obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        orbitJNI.delete_Quants(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setNumberOfQuants(int value) {
    orbitJNI.Quants_numberOfQuants_set(swigCPtr, this, value);
  }

  public int getNumberOfQuants() {
    return orbitJNI.Quants_numberOfQuants_get(swigCPtr, this);
  }

  public void setQuantSizeOfSec(double value) {
    orbitJNI.Quants_quantSizeOfSec_set(swigCPtr, this, value);
  }

  public double getQuantSizeOfSec() {
    return orbitJNI.Quants_quantSizeOfSec_get(swigCPtr, this);
  }

  public Quants() {
    this(orbitJNI.new_Quants(), true);
  }

}
