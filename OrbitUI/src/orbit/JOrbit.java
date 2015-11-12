package orbit;

public class JOrbit {

	static {
		System.loadLibrary("orbit");
	}
	native public void CreateTrajectory(double initX,double initY,double initZ,
			   double orX,double orY,double orZ,
			   double shipmass, double fuelmass,
			   double length,
			   double maxrotX,double maxrotY,double maxrotZ,
			   double fueluasge,double impulse,
			   double overload, double heating,
			   int quantsizeofsec, int quantnumber);
}
