using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace Memory_Game
{

    public partial class Form1 : Form
    {
        //sets a clicked variable to keep track of screen clicks
        int clicks = 0;

        //counts how many matches to know when the game is over
        int matches = 0;

        public Form1()
        {
            //creates an array with the pictures for placement on the board
            Bitmap[] cardOptions = new Bitmap[6];
            cardOptions[0] = Properties.Resources.baseball_player;
            cardOptions[1] = Properties.Resources.book;
            cardOptions[2] = Properties.Resources.bug;
            cardOptions[3] = Properties.Resources.dog;
            cardOptions[4] = Properties.Resources.football;
            cardOptions[5] = Properties.Resources.robot;

            
            InitializeComponent();

            //turns of the textboxs holding the status updates
            textBox2.Visible = false;


            //initializes the cardbacks
            pictureBox1.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox2.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox3.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox4.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox5.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox6.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox7.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox8.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox9.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox10.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox11.Image = global::Memory_Game.Properties.Resources.card_back;
            pictureBox12.Image = global::Memory_Game.Properties.Resources.card_back;

            //creates an array of booleans corresponding to the placement of new
            //cards
            bool[] placed = new bool[12];
            for (int i=0; i < 12; i++)
            {
                placed[i] = false;
            }

            //creates an array full of the locations of the pictures for assignment
            //during runtime events
            Bitmap[] cardImages = new Bitmap[12];

            //deals the cards
            Random random = new Random();
            for(int i =0; i<6; i++)
            {
                //finds two random open spots for placing cards
                int number1 = random.Next(0, 12);
                int number2 = random.Next(0, 12);
                while (placed[number1])
                {
                    number1 = random.Next(0, 12);
                }
                placed[number1] = true; //marks the first number as placed 
                while (placed[number2])
                {
                    number2 = random.Next(0, 12);
                }
                placed[number2] = true; //marks the second number as placed

                //places the image in those two spots in the cardImages array
                cardImages[number1] = cardOptions[i];
                cardImages[number2] = cardOptions[i];
            }

            //places the card images as background images
            pictureBox1.BackgroundImage = cardImages[0];
            pictureBox2.BackgroundImage = cardImages[1];
            pictureBox3.BackgroundImage = cardImages[2];
            pictureBox4.BackgroundImage = cardImages[3];
            pictureBox5.BackgroundImage = cardImages[4];
            pictureBox6.BackgroundImage = cardImages[5];
            pictureBox7.BackgroundImage = cardImages[6];
            pictureBox8.BackgroundImage = cardImages[7];
            pictureBox9.BackgroundImage = cardImages[8];
            pictureBox10.BackgroundImage = cardImages[9];
            pictureBox11.BackgroundImage = cardImages[10];
            pictureBox12.BackgroundImage = cardImages[11];
        }
        //all pictureboxes toggle their image on and off to reveal their background imgae
        //when clicked on
        private void pictureBox3_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox3);
                clicks++;
            }
            else
                GiveDirection();
        }
        //see picturebox3's comment
        private void pictureBox2_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox2);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox4_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox4);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox7_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox7);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox6_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox6);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox1);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox11_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox11);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox12_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox12);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox10_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox10);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox8_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox8);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox9_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox9);
                clicks++;
            }
            else
                GiveDirection();
        }

        //see picturebox3's comment
        private void pictureBox5_MouseClick(object sender, MouseEventArgs e)
        {
            if (clicks != 2)
            {
                textBox2.Visible = false;
                ToggleImage(pictureBox5);
                clicks++;
            }
            else
                GiveDirection();
        }

        //toggles the image on and off
        private void ToggleImage(PictureBox box)
        {
            if (box.Image != null)
                box.Image = null;
            else
                box.Image = global::Memory_Game.Properties.Resources.card_back;
        }

        //checks whether the two flipped pictures are matches
        private void CheckForMatch()
        { 
            //creates an array of the current states of the boxes for checking which
            //two boxes were clicked
            PictureBox[] boxes = new PictureBox[12];
            boxes[0] = this.pictureBox1;
            boxes[1] = this.pictureBox2;
            boxes[2] = this.pictureBox3;
            boxes[3] = this.pictureBox4;
            boxes[4] = this.pictureBox5;
            boxes[5] = this.pictureBox6;
            boxes[6] = this.pictureBox7;
            boxes[7] = this.pictureBox8;
            boxes[8] = this.pictureBox9;
            boxes[9] = this.pictureBox10;
            boxes[10] = this.pictureBox11;
            boxes[11] = this.pictureBox12;

            //finds the two clicked boxes
            int clicked1=0, clicked2=0, count=0;
            for(int i =0; i <12; i++)
             {
                 if (boxes[i].Image == null && boxes[i].Enabled == true)
                     {
                         if (count == 1)
                             clicked2 = i;
                         else
                         {
                             clicked1 = i;
                             count++;
                         }
                     }
             }

                //compares the two boxes. if matched displays success
                //else displays try again
             if (boxes[clicked1].BackgroundImage == boxes[clicked2].BackgroundImage)
                 {
                     this.textBox2.Text = "Thats a Match!!" ;
                     this.textBox2.Visible = true;
                     Thread.Sleep(1000); //pauses for two seconds
                     //disables the two matched boxes 
                     boxes[clicked1].Enabled = false;
                     boxes[clicked2].Enabled = false;
                     clicks = 0;
                     matches++;

                 }
                 else //boxes did not match
                 {
                     this.textBox2.Text = "Sorry, try again!!";
                     this.textBox2.Visible = true;
                     Thread.Sleep(1000); //pauses
                     //resets the pictures
                     boxes[clicked1].Image = global::Memory_Game.Properties.Resources.card_back;
                     boxes[clicked2].Image = global::Memory_Game.Properties.Resources.card_back;
                     clicks = 0;
                 }
             //all matches have been found. closes the game
             if (matches == 6)
             {
                 textBox2.Text = "Game over! YOU WON!!!";
             }
        }
        

        //this button initiates the check match 
        private void button1_Click(object sender, EventArgs e)
        {
            if (clicks == 0 || clicks == 1)
            {
                textBox2.Text = "You MUST click two boxes!";
                textBox2.Visible = true;
                ResetBoxes();
                clicks = 0;
            }
            else
            {
                CheckForMatch();
            }

        }

        //resets the boxes in the case the user tries to check 1 or 0 cards
        private void ResetBoxes()
        {
            //creates array of current standing of boxes
            PictureBox[] boxes = new PictureBox[12];
            boxes[0] = this.pictureBox1;
            boxes[1] = this.pictureBox2;
            boxes[2] = this.pictureBox3;
            boxes[3] = this.pictureBox4;
            boxes[4] = this.pictureBox5;
            boxes[5] = this.pictureBox6;
            boxes[6] = this.pictureBox7;
            boxes[7] = this.pictureBox8;
            boxes[8] = this.pictureBox9;
            boxes[9] = this.pictureBox10;
            boxes[10] = this.pictureBox11;
            boxes[11] = this.pictureBox12;

            for(int i =0; i<12; i ++)
            {
                if (boxes[i].Image == null && boxes[i].Enabled == true)
                {
                    boxes[i].Image = global::Memory_Game.Properties.Resources.card_back;
                }
            }
        }

        //tells the user what to do
        private void GiveDirection()
        {
            //displays textbox telling user to click check matches
            textBox2.Text = "Click Check Cards!";
            textBox2.Visible = true;
        }

     
    }

}
