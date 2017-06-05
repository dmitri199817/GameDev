using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Camera : MonoBehaviour {

	public Material[] materials;

	// Use this for initialization
	void Start () {
		GetComponent<Skybox> ().material = materials [Random.Range(0, materials.Length)]; 	
	}


}
