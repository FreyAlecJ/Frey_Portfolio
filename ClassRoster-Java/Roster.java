import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import java.util.Iterator;
import java.util.regex.Pattern;

public class Roster {
	
	private ArrayList<Student> rosterList;
	
	public Roster () {
		rosterList = new ArrayList<Student>();
	}
	
	public void displayRoster() {
		System.out.printf("%7s %6s %6s %6s %6s %6s %6s %6s %6s\n", "C#", "CLA", "OLA", "QUIZ", "EXAM", "HMWK", "BONUS",
						"TOTAL", "GRADE");
		for(Student kid : this.rosterList){
			kid.displayStudent();
		}
	}
	
	public void readData(File fileName) {
		
		try {
			FileInputStream fileIn = new FileInputStream(fileName);
			BufferedReader buffIn = new BufferedReader(new InputStreamReader(fileIn));
			
			String line = null;
			line = buffIn.readLine(); // burn the first line
			while ((line = buffIn.readLine()) != null) {
				
				String[] splits = line.split("\\s+");
				//set the students respective field...CLA OLA QUIZ HMWK EXAM BONUS 
				this.rosterList.add(new Student(splits[0], Integer.parseInt(splits[1]), Integer.parseInt(splits[2]),
						Integer.parseInt(splits[3]), Integer.parseInt(splits[4]), Integer.parseInt(splits[5]),
						Integer.parseInt(splits[6])));
			}
			buffIn.close();
		} catch (FileNotFoundException e) {
			System.out.println("File Name was not found!");
		} catch (IOException e) {
			System.out.println("Error while attempting to read file");
		}
	}
	
	public void displayMenu() {
		System.out.println("-----------Welcome to your Class Management System!-----------");
		System.out.println("-- 1. Display Students                                      --");
		System.out.println("-- 2. Add Student                                           --");
		System.out.println("-- 3. Remove Student                                        --");
		System.out.println("-- 4. Update Student                                        --");
		System.out.println("-- 5. Quit                                                  --");
		System.out.println("--------------------------------------------------------------");
	}
	
	public Boolean validateInput(String input) {
		try {
			Integer.parseInt(input);
			return true;
		} catch(NumberFormatException e) {
			return false;
		}
	}
	
	public void removeStudent(Scanner input) {
		//get id from the user
		System.out.println("Please enter the ID (in form of cXXXXXX) of the student you wish to remove");
		String id = input.nextLine();
		
		//validate the number is of the form 'cXXXXXX'
		Pattern pattern = Pattern.compile("^c[0-9]{6}$");
		if (!pattern.matcher(id).matches()) {
			System.out.println("Invalid ID. Returning to menu");
		}
		System.out.println(""); //print a line
		
		Iterator<Student> it = this.rosterList.iterator();
		
		while(it.hasNext()) {
			Student nextStudent = it.next();
			if (nextStudent.getID().equals(id)) {
				it.remove();
				System.out.println("Student " + id + " removed!\n");
				return;
			}
		}
		
		System.out.println("Student Not present in list\n");
		
	}
	
	public void addStudent(Scanner input){
		
		//declare a scanner for gathering user input
		System.out.println("Please enter the student's ID Number of form cXXXXXX");
		String id = input.nextLine();
		
		//validate the number is of the form 'cXXXXXX'
		Pattern pattern = Pattern.compile("^c[0-9]{6}$");
		if (!pattern.matcher(id).matches()) {
			System.out.println("Invalid ID. Returning to menu");
		}
		System.out.println(""); //print a line
		
		//get cla score
		System.out.println("Please enter the student's CLA score");
		String claStr = input.nextLine();
		int cla = -1;
		if (this.validateInput(claStr)){
			cla = Integer.parseInt(claStr);
			System.out.println("");
		} else {
			System.out.println("Invalid CLA score, returning to menu");
			return;
		}
		
		//get ola score
		System.out.println("Please enter the student's OLA score");
		String olaStr = input.nextLine();
		int ola = -1;
		if (this.validateInput(olaStr)){
			ola = Integer.parseInt(olaStr);
			System.out.println("");
		} else {
			System.out.println("Invalid OLA score, returning to menu");
			return;
		}
		
		//get quiz score
		System.out.println("Please enter the student's Quiz score");
		String quizStr = input.nextLine();
		int quiz = -1;
		if (this.validateInput(quizStr)){
			quiz = Integer.parseInt(quizStr);
			System.out.println("");
		} else {
			System.out.println("Invalid Quiz score, returning to menu");
			return;
		}
		
		//get hmwk score
		System.out.println("Please enter the student's Homework score");
		String hmwkStr = input.nextLine();
		int hmwk = -1;
		if (this.validateInput(hmwkStr)){
			hmwk = Integer.parseInt(hmwkStr);
			System.out.println("");
		} else {
			System.out.println("Invalid Homework score, returning to menu");
			return;
		}
		
		//get exam score
		System.out.println("Please enter the student's Exam score");
		String examStr = input.nextLine();
		int exam = -1;
		if (this.validateInput(examStr)){
			exam = Integer.parseInt(examStr);
			System.out.println("");
		} else {
			System.out.println("Invalid Exam score, returning to menu");
			return;
		}
		
		//get bonus score
		System.out.println("Please enter the student's Bonus score");
		String bonusStr = input.nextLine();
		int bonus = -1;
		if (this.validateInput(bonusStr)){
			bonus = Integer.parseInt(bonusStr);
			System.out.println("");
		} else {
			System.out.println("Invalid bonus score, returning to menu");
			return;
		}
		
		//add student to roster
		Student newStudent = new Student(id, cla, ola, quiz, hmwk, exam, bonus);
		this.rosterList.add(newStudent);
		
		System.out.println("Student added!");
		
	}
	
	public void updateStudent(Scanner input) {
		//get id from the user
		System.out.println("Please enter the ID (in form of cXXXXXX) of the student you wish to update");
		String id = input.nextLine();
			
		//validate the number is of the form 'cXXXXXX'
		Pattern pattern = Pattern.compile("^c[0-9]{6}$");
		if (!pattern.matcher(id).matches()) {
			System.out.println("Invalid ID. Returning to menu");
			}
		System.out.println(""); //print a line
		
		//find the student
		Iterator<Student> it = this.rosterList.iterator();
		Student student = null;
		while(it.hasNext()) {
			student = it.next();
			if (student.getID().equals(id)) {
				break;
			}
		}
		
		if (!it.hasNext() && !student.getID().equals(id)){
			System.out.println("Student not found! Returning to menu");
			return;
		}
		
		//prompt user to update values
		System.out.println("What value would you like to update?");
		System.out.println("1. CLA");
		System.out.println("2. OLA");
		System.out.println("3. Quiz");
		System.out.println("4. Homework");
		System.out.println("5. Exam");
		System.out.println("6. Bonus");
		String userInput = input.nextLine();
		if (this.validateInput(userInput)) {
			int option = Integer.parseInt(userInput);
			System.out.println("What is the new value?");
			String updatedValue = input.nextLine();
			if (this.validateInput(updatedValue)) {
				int updatedInt = Integer.parseInt(updatedValue);
				switch (option) {
				case 1:
					student.setCLA(updatedInt);
					break;
				case 2 :
					student.setOLA(updatedInt);
					break;
				case 3 :
					student.setQuiz(updatedInt);
					break;
				case 4 :
					student.setHomeWork(updatedInt);
					break;
				case 5 :
					student.setExam(updatedInt);
					break;
				case 6 : 
					student.setBonus(updatedInt);
					break;
				default :
					System.out.println("Returning to menu!");
					return;
					
				}
			} else {
				System.out.println("Invalid value, returning to menu.");
			}
		} else {
			System.out.println("Invalid choice, returning to menu.");
			return;
		}
		
		System.out.println("");
		System.out.println("Student Updated!");
		
	}
	
	public static void main(String[] args) {
		
		//create a new Roster
		Roster myRoster = new Roster();
		
		//build the roster array based off text file
		File fileName = new File("data.txt");
		myRoster.readData(fileName);
		
		//declare scanner 
		Scanner userIn = new Scanner(System.in);
		
		//create menu for UI
		Boolean keepGoing = true;
		while(keepGoing) {
			//display menu
			myRoster.displayMenu();
			
			//get user input
			System.out.println("What can I help you with today?");
			String userInput = userIn.nextLine();
			
			//validate user input is a number
			if (myRoster.validateInput(userInput)) {
				int selection = Integer.parseInt(userInput);
				
				switch (selection) {
				case 1 : 
					myRoster.displayRoster();
					System.out.println("");
					break;
				case 2 : 
					myRoster.addStudent(userIn);
					System.out.println("");
					break;
				case 3 :
					myRoster.removeStudent(userIn);
					System.out.println("");
					break;
				case 4 : 
					myRoster.updateStudent(userIn);
					System.out.println("");
					break;
				case 5 :
					System.out.println("Thank you for using Class Management System!");
					keepGoing = false;
					break;
				default : 
					System.out.println("Please enter a valid integer between 1 and 4");
				}//end switch
				
			} else {
				System.out.println("Please enter a valid integer between 1 and 4");
			} //end if/else
			
		}//end while
		userIn.close();
		
		
	}
}
