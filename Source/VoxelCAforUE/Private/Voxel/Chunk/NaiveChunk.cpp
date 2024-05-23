// Fill out your copyright notice in the Description page of Project Settings.


#include "NaiveChunk.h"

#include "Voxel/Utils/FastNoiseLite.h"

void ANaiveChunk::Setup()
{
	// Initialize Blocks
	Blocks.SetNum(Size * Size * Size);
}

void ANaiveChunk::Generate2DHeightMap(const FVector Position)
{
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			const float Xpos = x + Position.X;
			const float ypos = y + Position.Y;
			
			const int Height = FMath::Clamp(FMath::RoundToInt((Noise->GetNoise(Xpos, ypos) + 1) * Size / 2), 0, Size);

			for (int z = 0; z < Height; z++)
			{
				Blocks[GetBlockIndex(x,y,z)] = EBlock::Stone;
			}

			for (int z = Height; z < Size; z++)
			{
				Blocks[GetBlockIndex(x,y,z)] = EBlock::Air;
			}
			
		}
	}
}

void ANaiveChunk::Generate3DHeightMap(const FVector Position)
{
	for (int x = 0; x < Size; ++x)
	{
		for (int y = 0; y < Size; ++y)
		{
			for (int z = 0; z < Size; ++z)
			{
				const auto NoiseValue = Noise->GetNoise(x + Position.X, y + Position.Y, z + Position.Z);

				if (NoiseValue >= 0)
				{
					Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
				}
				else
				{
					Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
				}
			}
		}
	}
}


//Dynamic modifications
void ANaiveChunk::Edit2DHeightMap()
{
	int seed = time(0);
	srand(seed);
	int r;

	//for (int z = (Size - 1); z > 24; z--)
	//{
//		for (int x = 13; x < 17; x++)
//		{
//			for (int y = 0; y < Size; y++)
//			{
//
//				if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Air) && (Blocks[GetBlockIndex(x, y, z - 1)] == EBlock::Stone))
//				{
//					int counter = 0;
//
//					if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//
//					if (counter == 0)
//					{
//						r = rand() % 10;
//
//						if (r < 2) {
//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
//						}
//
//					}
//					else if ((counter == 1) || (counter == 2)){
//
//						r = rand() % 10;
//
//						if (r < 7) {
//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
//						}
//					}
//					else if ((counter == 3) || (counter == 4)) {
//
//						r = rand() % 10;
//
//						if (r < 4) {
//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
//						}
//					}
//					else if ((counter == 5) || (counter == 6)) {
//
//						r = rand() % 10;
//
//						if (r < 3) {
//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
//						}
//					}
//					//else {
//
//					//	r = rand() % 10;
//
//					//	if (r < 2) {
//					//		Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
//					//	}
//					//}
//				}
//
//			}
//		}
//	}
//
//	for (int z = 24; z > 19; z--)
//	{
//		for (int x = 10; x < 20; x++)
//		{
//			for (int y = 0; y < Size; y++)
//			{
//
//				if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Air) && (Blocks[GetBlockIndex(x, y, z - 1)] == EBlock::Stone))
//				{
//					int counter = 0;
//
//					if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//					if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
//					{
//						counter++;
//					}
//
//					if (counter == 0)
//					{
//						r = rand() % 10;
//
//						if (r < 2) {
//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
//						}
//
//					}
//					else if (counter == 1) {
//						r = rand() % 10;
//
//						if (r < 7) {
//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
//						}
//					}
//					else if ((counter == 2) || (counter == 3)) {
//						r = rand() % 10;
//
//						if (r < 5) {
//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
//						}
//					}
//					else if ((counter == 5) || (counter == 6)) {
//						r = rand() % 10;
//
//						if (r < 3) {
//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
//						}
//					}
					//else {

					//	r = rand() % 10;

					//	if (r < 3) {
					//		Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
					//	}
					//}
	//			}

	//		}
	//	}
	//}

	//for (int z = Size - 1; z > 1; z--) 
	//{
	//	for (int x = 0; x < (Size / 2); x++)
	//	{
	//		for (int y = 9; y < 19; y++)
	//		{
	//			//generating mountains with 0,2 chance
	//			//if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Air) && (Blocks[GetBlockIndex(x, y, z - 1)] == EBlock::Stone))
	//			//{

	//			//	r = rand() % 10;

	//			//	if (r < 2) {
	//			//		Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
	//			//	}
	//			//}

	//			//deactivating with a chance
	//			//if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Stone) && (Blocks[GetBlockIndex(x, y, z + 1)] == EBlock::Air))
	//			//{

	//			//	r = rand() % 10;

	//			//	if (r < 5) {
	//			//		Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
	//			//	}
	//			//}


	//			if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Stone) && (Blocks[GetBlockIndex(x, y, z + 1)] == EBlock::Air))
	//			{

	//				int counter = 0;

	//				if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}

	//				//if ((counter >= 0) && (counter < 7))
	//				//{
	//				//	Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;

	//				//}

	//				if (counter == 6)
	//				{

	//					r = rand() % 10;

	//					if (r < 8) {
	//						Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
	//					}
	//				}

	//				else if (counter == 5)
	//				{

	//					r = rand() % 10;

	//					if (r < 4) {
	//						Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
	//					}
	//				}
	//				//		//Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;

	//				//	}
	//				//	else if ((counter >= 2) && (counter < 5)) {

	//				//		r = rand() % 10;

	//				//		if (r < 6) {
	//				//			Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
	//				//		}
	//				//	}
	//				//	else if ((counter >= 0) && (counter < 2)) {

	//				//		r = rand() % 10;

	//				//		if (r < 4) {
	//				//			Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
	//				//		}
	//				//	}

	//			}


	//			//else
	//			else if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Air) && (Blocks[GetBlockIndex(x, y, z - 1)] == EBlock::Stone))
	//			{
	//				int counter = 0;

	//				if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}
	//				if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
	//				{
	//					counter++;
	//				}

	//				if (counter > 1)
	//				{
	//					Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;

	//				}

	//				/*if ((counter == 3))
	//				{
	//					Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;

	//				}
	//				else if (counter == 2) {

	//					r = rand() % 10;

	//					if (r < 3) {
	//						Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
	//					}
	//				}
	//				else if (counter == 4) {

	//					r = rand() % 10;

	//					if (r < 5) {
	//						Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
	//					}
	//				}*/
	//			}


	//		}
	//	}
	//		for (int x = (Size / 2); x < Size; x++)
	//		{
	//			for (int y = 11; y < 21; y++)
	//			{

	//				if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Stone) && (Blocks[GetBlockIndex(x, y, z + 1)] == EBlock::Air))
	//				{

	//					int counter = 0;

	//					if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}

	//					if (counter == 6)
	//					{

	//						r = rand() % 10;

	//						if (r < 8) {
	//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
	//						}
	//					}

	//					else if (counter == 5)
	//					{

	//						r = rand() % 10;

	//						if (r < 4) {
	//							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
	//						}
	//					}


	//				}


	//				else if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Air) && (Blocks[GetBlockIndex(x, y, z - 1)] == EBlock::Stone))
	//				{
	//					int counter = 0;

	//					if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}
	//					if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
	//					{
	//						counter++;
	//					}

	//					if (counter > 1)
	//					{
	//						Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;

	//					}


	//				}


	//			}
	//		}
	//	}
	

		//Levels of height

for (int z = (Size - 1); z > 16; z--)
{
	for (int x = 7; x < 23; x++)
	{
		for (int y = 0; y < Size; y++)
		{

			if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Stone) && (Blocks[GetBlockIndex(x, y, z + 1)] == EBlock::Air))
			{

				int counter = 0;

				if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
				{
					counter++;
				}
				if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
				{
					counter++;
				}
				if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
				{
					counter++;
				}
				if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
				{
					counter++;
				}
				if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
				{
					counter++;
				}
				if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
				{
					counter++;
				}
				if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
				{
					counter++;
				}
				if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
				{
					counter++;
				}

				if (counter == 0)
				{
					Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;

				}
				else if (counter == 1) {
					r = rand() % 10;

					if (r < 8) {
						Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
					}
				}
				else {

					r = rand() % 10;

					if (r < 4) {
						Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
					}



				}

			}
		}
	}
}



	for (int z = 16; z > 11; z--)
	{
		for (int x = 9; x < 21; x++)
		{
			for (int y = 0; y < Size; y++)
			{

				if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Stone) && (Blocks[GetBlockIndex(x, y, z + 1)] == EBlock::Air))
				{

					int counter = 0;

					if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}

					if (counter == 0)
					{
						Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;

					}
					else if (counter == 1) {
						r = rand() % 10;

						if (r < 8) {
							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
						}
					}
					else {

						r = rand() % 10;

						if (r < 4) {
							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
						}



					}

				}
			}
		}
	}



	for (int z = 11; z > 7; z--)
	{
		for (int x = 10; x < 20; x++)
		{
			for (int y = 0; y < Size; y++)
			{

				if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Stone) && (Blocks[GetBlockIndex(x, y, z + 1)] == EBlock::Air))
				{

					int counter = 0;

					if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}

					if (counter == 0)
					{
						Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;

					}
					else if (counter == 1) {
						r = rand() % 10;

						if (r < 8) {
							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
						}
					}
					else {

						r = rand() % 10;

						if (r < 4) {
							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
						}



					}

				}
			}
		}
	}

	for (int z = 7; z > 3; z--)
	{
		for (int x = 12; x < 18; x++)
		{
			for (int y = 0; y < Size; y++)
			{

				if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Stone) && (Blocks[GetBlockIndex(x, y, z + 1)] == EBlock::Air))
				{
					int counter = 0;

					if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}

					if (counter == 0)
					{
						Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;

					} 
					else if (counter == 1) {
						r = rand() % 10;

						if (r < 8) {
							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
						}
					}
					else {

						r = rand() % 10;

						if (r < 4) {
							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
						}
					}
				}

			}
		}
	}

	for (int z = 3; z > 1; z--)
	{
		for (int x = 14; x < 16; x++)
		{
			for (int y = 0; y < Size; y++)
			{

				if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Stone) && (Blocks[GetBlockIndex(x, y, z + 1)] == EBlock::Air))
				{
					int counter = 0;

					if (Blocks[GetBlockIndex(x + 1, y, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x + 1, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x + 1, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y + 1, z)] == EBlock::Stone)
					{
						counter++;
					}
					if (Blocks[GetBlockIndex(x - 1, y - 1, z)] == EBlock::Stone)
					{
						counter++;
					}

					if (counter == 0)
					{
						Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;

					}
					else if (counter == 1) {
						r = rand() % 10;

						if (r < 8) {
							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
						}
					}
					else if ((counter == 3) || (counter == 4)) {
						r = rand() % 10;

						if (r < 2) {
							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
						}
					}
					else {

						r = rand() % 10;

						if (r < 3) {
							Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
						}
					}
				}

			}
		}
	}

	//for (int z = 5; z > 2; z--)
	//{
	//	for (int x = 14; x < 16; x++)
	//	{
	//		for (int y = 0; y < Size; y++)
	//		{

	//			if ((Blocks[GetBlockIndex(x, y, z)] == EBlock::Stone) && (Blocks[GetBlockIndex(x, y, z + 1)] == EBlock::Air))
	//			{

	//				r = rand() % 10;

	//				if (r < 2) {
	//					Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
	//				}
	//			}

	//		}
	//	}
	//}
 }


void ANaiveChunk::GenerateMesh()
{
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			for (int z = 0; z < Size; z++)
			{
				if (Blocks[GetBlockIndex(x,y,z)] != EBlock::Air)
				{
					const auto Position = FVector(x,y,z);
					
					for (auto Direction : {EDirection::Forward, EDirection::Right, EDirection::Back, EDirection::Left, EDirection::Up, EDirection::Down})
					{
						if (Check(GetPositionInDirection(Direction, Position)))
						{
							CreateFace(Direction, Position * 100);
						}
					}
				}
			}
		}
	}
}

bool ANaiveChunk::Check(const FVector Position) const
{
	if (Position.X >= Size || Position.Y >= Size || Position.X < 0 || Position.Y < 0 || Position.Z < 0) return true;
	if (Position.Z >= Size) return true;
	return Blocks[GetBlockIndex(Position.X, Position.Y, Position.Z)] == EBlock::Air;
}

void ANaiveChunk::CreateFace(const EDirection Direction, const FVector Position)
{
	const auto Color = FColor::MakeRandomColor();
	const auto Normal = GetNormal(Direction);
	
	MeshData.Vertices.Append(GetFaceVertices(Direction, Position));
	MeshData.Triangles.Append({ VertexCount + 3, VertexCount + 2, VertexCount, VertexCount + 2, VertexCount + 1, VertexCount });
	MeshData.Normals.Append({Normal, Normal, Normal, Normal});
	MeshData.Colors.Append({Color, Color, Color, Color});
	MeshData.UV0.Append({ FVector2D(1,1), FVector2D(1,0), FVector2D(0,0), FVector2D(0,1) });

	VertexCount += 4;
}

TArray<FVector> ANaiveChunk::GetFaceVertices(EDirection Direction, const FVector Position) const
{
	TArray<FVector> Vertices;

	for (int i = 0; i < 4; i++)
	{
		Vertices.Add(BlockVertexData[BlockTriangleData[i + static_cast<int>(Direction) * 4]] + Position);
	}
	
	return Vertices;
}

FVector ANaiveChunk::GetPositionInDirection(const EDirection Direction, const FVector Position) const
{
	switch (Direction)
	{
	case EDirection::Forward: return Position + FVector::ForwardVector;
	case EDirection::Back: return Position + FVector::BackwardVector;
	case EDirection::Left: return Position + FVector::LeftVector;
	case EDirection::Right: return Position + FVector::RightVector;
	case EDirection::Up: return Position + FVector::UpVector;
	case EDirection::Down: return Position + FVector::DownVector;
	default: throw std::invalid_argument("Invalid direction");
	}
}

FVector ANaiveChunk::GetNormal(const EDirection Direction) const
{
	switch (Direction)
	{
	case EDirection::Forward: return FVector::ForwardVector;
	case EDirection::Right: return FVector::RightVector;
	case EDirection::Back: return FVector::BackwardVector;
	case EDirection::Left: return FVector::LeftVector;
	case EDirection::Up: return FVector::UpVector;
	case EDirection::Down: return FVector::DownVector;
	default: throw std::invalid_argument("Invalid direction");
	}
}

void ANaiveChunk::ModifyVoxelData(const FIntVector Position, const EBlock Block)
{
	const int Index = GetBlockIndex(Position.X, Position.Y, Position.Z);
	
	Blocks[Index] = Block;
}

int ANaiveChunk::GetBlockIndex(const int X, const int Y, const int Z) const
{
	return Z * Size * Size + Y * Size + X;
}

