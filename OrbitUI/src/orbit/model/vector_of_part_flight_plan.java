package orbit.model;

public class vector_of_part_flight_plan {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected vector_of_part_flight_plan(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(vector_of_part_flight_plan obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        orbitJNI.delete_vector_of_part_flight_plan(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public vector_of_part_flight_plan() {
    this(orbitJNI.new_vector_of_part_flight_plan__SWIG_0(), true);
  }

  public vector_of_part_flight_plan(long n) {
    this(orbitJNI.new_vector_of_part_flight_plan__SWIG_1(n), true);
  }

  public long size() {
    return orbitJNI.vector_of_part_flight_plan_size(swigCPtr, this);
  }

  public long capacity() {
    return orbitJNI.vector_of_part_flight_plan_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    orbitJNI.vector_of_part_flight_plan_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return orbitJNI.vector_of_part_flight_plan_isEmpty(swigCPtr, this);
  }

  public void clear() {
    orbitJNI.vector_of_part_flight_plan_clear(swigCPtr, this);
  }

  public void add(PartOfFlightPlan x) {
    orbitJNI.vector_of_part_flight_plan_add(swigCPtr, this, PartOfFlightPlan.getCPtr(x), x);
  }

  public PartOfFlightPlan get(int i) {
    return new PartOfFlightPlan(orbitJNI.vector_of_part_flight_plan_get(swigCPtr, this, i), false);
  }

  public void set(int i, PartOfFlightPlan val) {
    orbitJNI.vector_of_part_flight_plan_set(swigCPtr, this, i, PartOfFlightPlan.getCPtr(val), val);
  }

}
