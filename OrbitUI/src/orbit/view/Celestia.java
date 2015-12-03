package orbit.view;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement
public class Celestia {
	String path;
	String trajectoryPath;

	public String getPath(){
		return path;
	}

	public String getPathToTrajectory(){
		return trajectoryPath;
	}

	@XmlElement
	public void setPath(String path){
		this.path = path;
	}
	@XmlElement
	public void setPathToTrajectory(String pathToExtra){
		this.trajectoryPath = pathToExtra;
	}
}
